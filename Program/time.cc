#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include "time.h"
#include<iostream>
#include<thread>
#include<vector>
#define TRC_CLASS_NAME "CTimeValidation"

using namespace std;

CTimeValidation::CTimeValidation()
    : mMillisecond(0)
    , lasttimestamp(0)
    , isInitialized(false)
    , timesaving(false)
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    lasttimestamp = tp.tv_sec;
    std::time_t origTime = std::time(nullptr);
    std::tm* tmp = std::gmtime(&origTime);
    if (nullptr != tmp) {
        std::memcpy(static_cast<void*>(&lastValidTime), static_cast<void*>(tmp), sizeof(std::tm));
    }
}
CTimeValidation::~CTimeValidation()
{
}

const int32_t CTimeValidation::MAX_MILLISECONDS = 10;
const int32_t CTimeValidation::TIMESTAMP_THRESHOLD = 3600;
CTimeValidation& CTimeValidation::getInstance()
{
    static CTimeValidation inst;
    return inst;
}

std::pair<std::string, std::string> CTimeValidation::getUniqueTimeStamp(
    int32_t hour, int32_t minute, int32_t second, int32_t year, int32_t month, int32_t day)
{
    std::stringstream s1, s2;
    int32_t millisecond = 0;
    if (!IsValidTimeAndDate(hour, minute, second, year, month, day)) {
	    //cout<<"Not a valid Time and Date"<<endl;
        struct timespec tp;
        clock_gettime(CLOCK_MONOTONIC, &tp);

        std::time_t timeSt = timegm(&getInstance().lastValidTime);

        std::time_t nr_sec = tp.tv_sec - getInstance().lasttimestamp;
        timeSt = timeSt + nr_sec;
        std::tm* tmp = std::gmtime(&timeSt);
        std::tm ctm;
        if (nullptr != tmp) {
            std::memcpy(static_cast<void*>(&ctm), static_cast<void*>(tmp), sizeof(std::tm));
        } else {
            printf("Unable to convert time");
            return std::pair<std::string, std::string>(s1.str(), s2.str());
        }
        year = ctm.tm_year % 100;
        month = ctm.tm_mon + 1;
        day = ctm.tm_mday;

        hour = ctm.tm_hour - (getInstance().timesaving ? 1 : 0);
        minute = ctm.tm_min;
        second = ctm.tm_sec;
    } else {
        getInstance().isInitialized = true;
    }

    // The time stamp must increase even if the message is sent in the same second

    if (hour == getInstance().lastValidTime.tm_hour && minute == getInstance().lastValidTime.tm_min
        && second == getInstance().lastValidTime.tm_sec) {
        getInstance().mMillisecond++;
	//cout<<"Time matches with previous one.Hence increment"<<getInstance().mMillisecond<<endl;
        if (MAX_MILLISECONDS < getInstance().mMillisecond) {
            getInstance().mMillisecond = 0;
        }
    } else {
        getInstance().mMillisecond = 0;
    }
    millisecond = getInstance().mMillisecond;
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    getInstance().lasttimestamp = tp.tv_sec;
    getInstance().lastValidTime.tm_hour = hour;
    getInstance().lastValidTime.tm_min = minute;
    getInstance().lastValidTime.tm_sec = second;
    getInstance().lastValidTime.tm_year = year + 100;
    getInstance().lastValidTime.tm_mon = month - 1;
    getInstance().lastValidTime.tm_mday = day;

    s1 << std::setw(2) << std::setfill('0') << hour;
    s1 << std::setw(2) << std::setfill('0') << minute;
    s1 << std::setw(2) << std::setfill('0') << second;
    s1 << ".";
    s1 << std::setw(2) << std::setfill('0')
       << millisecond; // we don't have UTC-Time millisecond. The receptionTimeStamp is in
                       // milliseconds. but it was milliseconds from startup. just use ".00"
//	cout<<"millisecond="<<millisecond<<endl;
//		cout<<"s1="<<s1.str()<<endl;

    s2 << std::setw(2) << std::setfill('0') << day;
    s2 << std::setw(2) << std::setfill('0') << month;
    s2 << std::setw(2) << std::setfill('0') << year;

    return std::pair<std::string, std::string>(s1.str(), s2.str());
}

bool CTimeValidation::IsValidTimeAndDate(
    int32_t hour, int32_t minute, int32_t second, int32_t year, int32_t month, int32_t day)
{
    getInstance().timesaving = false;
    if (!(0 != year && 0 != month && 0 != day)) {
        // DBG_MSG(("Invalid date"));
		cout<<"Returning false from here 1"<<endl;
        return false;
    }

    std::tm newTime;
    std::memset(static_cast<void*>(&newTime), 0, sizeof(std::tm));
    newTime.tm_hour = hour;
    newTime.tm_min = minute;
    newTime.tm_sec = second;
    newTime.tm_year = year + 100;
    newTime.tm_mon = month - 1;
    newTime.tm_mday = day;
    newTime.tm_isdst = 0;
    newTime.tm_gmtoff = getInstance().lastValidTime.tm_gmtoff;
    std::tm temp;
    std::memcpy(
        static_cast<void*>(&temp),
        static_cast<void*>(&(getInstance().lastValidTime)),
        sizeof(std::tm));

    std::time_t oldDate = timegm(&temp);

    if (temp.tm_hour != getInstance().lastValidTime.tm_hour) {
        getInstance().timesaving = true;
    }

    std::time_t newData = std::mktime(&newTime);
    //cout<<"newDate="<<newData<<endl;
    //cout<<"oldDate="<<oldDate<<endl;

    if (!getInstance().isInitialized) {
//		cout<<"Returning from here 7"<<endl;
        return true;
    }

    if (std::abs(newData - oldDate) > TIMESTAMP_THRESHOLD) {
//		cout<<"Returning from here 8"<<endl;
        return true;
    }

    if (newData > oldDate) {
//		cout<<"Returning from here 9"<<endl;
        return true;
    } else if (newData == oldDate) {
        if (getInstance().mMillisecond < MAX_MILLISECONDS - 1) {
//		cout<<"Returning from here 10"<<endl;
            return true;
        } else {
//		cout<<"Returning false from here 11"<<endl;
            return false;
        }
    } else {
//		cout<<"Returning false from here 12"<<endl;
        return false;
    }
//		cout<<"Returning false from here 13"<<endl;
    return false;
}

void task(int ThreadID)
{
	std::pair<std::string, std::string> TimeDate = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	/*std::pair<std::string, std::string> TimeDate1 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate1.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate2 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate2.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate3 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate3.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate4 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate4.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate5 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate5.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate6 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate6.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate7 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate7.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate8 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate8.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate9 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate9.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate10 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate10.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate11 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate11.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate12 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate12.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate13 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate13.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate14 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate14.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate15 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate15.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate16 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate16.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate17 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate17.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate18 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate18.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate19 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate19.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate20 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate20.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate21 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate21.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate22 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate22.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate23 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate23.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate24 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate24.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate25 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate25.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate26 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate26.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate27 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate27.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate28 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate28.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate29 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate29.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate30 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate30.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate31 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate31.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate32 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate32.first.c_str()<<"ThreadID="<<ThreadID<<endl;
	std::pair<std::string, std::string> TimeDate33 = CTimeValidation::getUniqueTimeStamp(13,20,5,2022%100,9,5);
	cout<<TimeDate33.first.c_str()<<"ThreadID="<<ThreadID<<endl;*/
}
int main()
{
		 std::vector<thread> threads(3);
		 for (int i = 0; i < 20; i++) {
     		   threads[1] = thread(task, i + 1);
     		   threads[2] = thread(task, i + 1);
     		   threads[3] = thread(task, i + 1);
		   threads[1].join();
		   threads[2].join();
		   threads[3].join();
    		}
}

