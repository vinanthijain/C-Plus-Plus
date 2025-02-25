#include <string>
#include <utility>
#include <ctime>

class CTimeValidation {
public:
    static std::pair<std::string, std::string> getUniqueTimeStamp(
        int32_t hour, int32_t minute, int32_t second, int32_t year, int32_t month, int32_t day);
    static bool IsValidTimeAndDate(
        int32_t hour, int32_t minute, int32_t second, int32_t year, int32_t month, int32_t day);

private:
    int32_t mMillisecond;
    std::time_t lasttimestamp;
    std::tm lastValidTime;
    bool isInitialized;
    bool timesaving = false;

    CTimeValidation();
    ~CTimeValidation();
    CTimeValidation(const CTimeValidation&) = delete;
    const CTimeValidation& operator=(const CTimeValidation&) = delete;
    static CTimeValidation& getInstance();

    static const int32_t MAX_MILLISECONDS;
    static const int32_t TIMESTAMP_THRESHOLD;
};

