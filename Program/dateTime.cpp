#include<iostream>
#include<stdio.h>
#include<optional>
using namespace std;

class DateType{
	int8_t day;
	int8_t month;
	int8_t year;
};
class Time{
	int8_t hours;
	int8_t minutes;
	int8_t seconds;
};
bool getTimeStamp(
    const std::optional<uint64_t>& timestamp)
{
    if (timestamp.has_value()) {
        time_t entryTime = timestamp.value();
        struct tm* callTimeFrmt = localtime(&entryTime);
        // set date
        cout<<"Date is "<<(callTimeFrmt->tm_mday)<<endl;
        cout<<"Month is "<<(callTimeFrmt->tm_mon)<<endl;
        cout<<"Year is "<<(
            (callTimeFrmt->tm_year + 1900)
            - 2000)<<endl; // struct tm considers 1900 & ::common:DateType takes from 2000
        // set time
        cout<<"Hour is "<<(callTimeFrmt->tm_hour)<<endl;
        cout<<"Minutes is "<<(callTimeFrmt->tm_min)<<endl;
        cout<<"Sec is "<<(callTimeFrmt->tm_sec)<<endl;
        return true;
    }
    return false;
}
int main()
{
	char unixTimeStamp[70];
        std::sprintf(unixTimeStamp, "0x%lx", 1695296956);
        cout<< "StartTimestamp:" << unixTimeStamp;
	//getTimeStamp(1695296956);
	getTimeStamp(unixTimeStamp);
}
