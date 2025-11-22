




#include <time.h>
#include <stdio.h>

int main(void){
        printf("Timezone : %d\n", (int)timezone);
        printf("Daylignt : %d\n", daylight);
        printf("TZname[0] : %s\n", tzname[0]);
        printf("TZname[1] : %s\n", tzname[1]);

        tzset();

	printf("Timezone : %d\n", (int)timezone);
        printf("Daylignt : %d\n", daylight);
        printf("TZname[0] : %s\n", tzname[0]);
        printf("TZname[1] : %s\n", tzname[1]);

	printf("-----------------------------\n");

	struct tm *tm;
	time_t * t;

	time(t);
	printf("Time(sec) : %d\n", (int)*t);

	tm = gmtime(t);
	printf("GMTIME=Y:%d ", tm->tm_year);
	printf("M: %d ", tm->tm_mon);
	printf("D: %d ", tm->tm_mday);
	printf("H: %d ", tm->tm_hour);
	printf("M: %d ", tm->tm_min);
	printf("S: %d \n", tm->tm_sec);

	tm = localtime(t);
        printf("GMTIME=Y:%d ", tm->tm_year);
        printf("M: %d ", tm->tm_mon);
        printf("D: %d ", tm->tm_mday);
        printf("H: %d ", tm->tm_hour);
        printf("M: %d ", tm->tm_min);
        printf("S: %d \n", tm->tm_sec);
	return 0;
}
