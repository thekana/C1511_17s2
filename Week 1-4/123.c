// localTime.c
// A program to test a function getLocalTime which determines the
// local time in a specified city, given the current UTC time.
//
// This program by Kanadech Jirapongtanavech (z5176970) on 2017-08-16
//
// Program stub created by Andrew Bennett on 2017-08-01.
// Version 1.0.4: Fix incorrect Lord Howe Island unit test.
// Version 1.0.3: Add version numbers.
// Version 1.0.2: Fixed include order.
// Version 1.0.1: Fix `CITY_LORD_HOWE_IS` symbol name.
// Version 1.0.0: First release onto an unsuspecting class.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE !TRUE

// =========== Cities ===========

// Australia
#define CITY_ADELAIDE 0
#define CITY_BRISBANE 1
#define CITY_BROKEN_HILL 2
#define CITY_CANBERRA 3
#define CITY_DARWIN 4
#define CITY_EUCLA 5
#define CITY_HOBART 6
#define CITY_LORD_HOWE_IS 7
#define CITY_MELBOURNE 8
#define CITY_PERTH 9
#define CITY_SYDNEY 10

// New Zealand
#define CITY_AUCKLAND 11
#define CITY_CHRISTCHURCH 12
#define CITY_WELLINGTON 13

// =========== Timezone Offsets ===========

// Australia
#define TIMEZONE_AWST 800 // Australian Western Standard Time

#define TIMEZONE_ACWST 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST 930 // Australian Central Standard Time
#define TIMEZONE_ACDT 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDR 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST 1200 // NZ Standard Time
#define TIMEZONE_NZDT 1300 // NZ Daylight Time


// =========== Function Prototypes ===========
// [DO NOT CHANGE THIS PROTOTYPE!]
int getLocalTime (int city, int day, int month, int timeUTC);
int NZ(int day, int month, int timeUTC);
int AUS_NODAYLIGHT (int city, int day, int month, int timeUTC);
int AUS_CENTRAL(int city, int day, int month, int timeUTC);
int AUS_EAST(int city, int day, int month, int timeUTC);
int ISLAND(int day, int month, int timeUTC);
int hour_24_format(int hour,int zone);

int main (int argc, char *argv[]) {

    // UTC time: 8:59am on 15th May, time in Christchurch: 8:59pm
    assert(getLocalTime(CITY_CHRISTCHURCH, 15, 5, 859) == 2059);

    // UTC time: midnight on 5th April, time in Sydney: 10am
    assert(getLocalTime(CITY_SYDNEY, 5, 4, 0) == 1000);

    // UTC time: 10:30am on 30th June, time in Adelaide: 8pm
    //assert(getLocalTime(CITY_ADELAIDE, 30, 6, 1030) == 2000);

    // UTC time: 8:15pm on 17th August, time in Brisane: 6:15am
    assert(getLocalTime(CITY_BRISBANE, 17, 8, 2015) == 615);

    // UTC time: 8am on 27th April, time in Auckland: 8pm
    assert(getLocalTime(CITY_AUCKLAND, 27, 4, 800) == 2000);

    // UTC time: 11:11pm on 30th January, time in Perth: 7:11am on the 31st
    assert(getLocalTime(CITY_PERTH, 30, 1, 2311) == 711);

    // UTC time: 8pm on 5th May, time in Perth: 4am on the 6th
    assert(getLocalTime(CITY_PERTH, 2, 5, 2000) == 400);

    // UTC time: 10:30pm on 6th Oct, time in Christchurch: 11:30am on the 7th
    assert(getLocalTime(CITY_CHRISTCHURCH, 6, 10, 2230) == 1130);

    // UTC time: 2:28pm on 16th December, time in Canberra: 1:28am on the 17th
    assert(getLocalTime(CITY_CANBERRA, 16, 12, 1428) == 128);

    // UTC time: 3:39am on 1st November, time in Darwin: 1:09pm
    assert(getLocalTime(CITY_DARWIN, 1, 11, 339) == 1309);

    // UTC time: 1pm on 8th July, time in Hobart: 11pm
    assert(getLocalTime(CITY_HOBART, 8, 7, 1300) == 2300);

    // UTC time: 1:54pm on 27th September, time in Melbourne: 11:54pm
    assert(getLocalTime(CITY_MELBOURNE, 27, 9, 1354) == 2354);

    // UTC time: 9:24am on 5th January, time in Wellington: 10:24pm
    assert(getLocalTime(CITY_WELLINGTON, 5, 1, 924) == 2224);

 // UTC time: 2pm on 18th April, time in Brisbane: 12:00am on the 19th
 assert(getLocalTime(CITY_BRISBANE, 18, 4, 1400) == 0);

 // UTC time: 11:06am on 8th October, time in Brisbane: 9:06pm
 assert(getLocalTime(CITY_BRISBANE, 8, 10, 1106) == 2106);

 // UTC time: 12:01pm on 29th October, time in Sydney: 11:01pm
 assert(getLocalTime(CITY_SYDNEY, 29, 10, 1201) == 2301);

 // UTC time: 11:45pm on 17th February, time in Darwin: 9:15am on the 18th
 assert(getLocalTime(CITY_DARWIN, 17, 2, 2345) == 915);

 // UTC time: 11pm on 7th August, time in Auckland: 10am on the 8th
 assert(getLocalTime(CITY_AUCKLAND, 7, 8, 2200) == 1000);

 // UTC time: 10:15 am on 5th September, time in Eucla: 7pm
 assert(getLocalTime(CITY_EUCLA, 5, 9, 1015) == 1900);

 // UTC time: 10am on 1st January, time in Broken Hill: 8:30pm
 assert(getLocalTime(CITY_BROKEN_HILL, 1, 1, 1000) == 2030);

 // UTC time: 10:15pm on 1st October, time in Lord Howe Island: 9:15am on the 2nd
 assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 10, 2215) == 915);

 // UTC time: 11:59pm on 6th February, time in Eucla: 8:44am on the 7th
 assert(getLocalTime(CITY_EUCLA, 6, 2, 2359) == 844);

 // UTC time: 1:17am on 17th July, time in Broken Hill: 10:47 am
 assert(getLocalTime(CITY_BROKEN_HILL, 17, 7, 117) == 1047);

 // UTC time: 2:00pm on 1st September, time in Auckland: 2:00am on the 2nd
 assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1400) == 200);

 // UTC time: 1:59pm on 1st September, time in Christchurch: 2:59am on the 2nd
 assert(getLocalTime(CITY_CHRISTCHURCH, 1, 4, 1359) == 259);

 // UTC time: 2:00pm on 23rd September, time in Wellington: 3:00am on the 24th
 assert(getLocalTime(CITY_WELLINGTON, 23, 9, 1400) == 300);

 // UTC time: 1:59pm on 23rd September, time in Auckland: 1:59am on the 24th
 assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1359) == 159);

 // UTC time 3.59pm on 30th Sep, time in Canberra: 1.59am on the 1st Oct
 assert(getLocalTime(CITY_CANBERRA, 30, 9, 1559) == 159);

 // UTC time 4.00pm on 30th Sep, time in Canberra: 3.00am on the 1st Oct
 assert(getLocalTime(CITY_CANBERRA, 30, 9, 1600) == 300);

 // UTC time 10.00pm on 1st Apr, time in Lord Howe Island: 8.30am on the 2nd
 assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 04, 2200) == 830);

 // UTC time 2.45pm on 1st Apr, time in Lord Howe Island: 1.45am on the 2nd
 assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 04, 1445) == 145);

 // UTC time 3.00pm on 1st Apr, time in Lord Howe Island: 1.30am on the 2nd
 assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 04, 1500) == 130);

 // UTC time 3.15pm on 30th Sep, time in Lord Howe Island: 1.45am on the 1st Oct
 assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1515) == 145);

 // UTC time 3.30pm on 30th Sep, time in Lord Howe Island: 2.30am on the 1st Oct
 assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);

 // UTC time: 0:54am on 7th February, time in Eucla: 9.39am
 assert(getLocalTime(CITY_EUCLA, 7, 2,54) == 939);


 printf("Good job your tests worked\n");

 return EXIT_SUCCESS;
}


// Converts the time to local time
// [DO NOT CHANGE THIS PROTOTYPE!]
int getLocalTime (int city, int day, int month, int timeUTC) {

 //assign function for each city
 int localTime = 0;
 int timeZone = 0;
 if (city >= 11) {
 timeZone = NZ(day, month, timeUTC);
 } else if (city == 1 || city == 4 || city == 5 || city == 9) {
 timeZone = AUS_NODAYLIGHT(city, day, month, timeUTC);
 } else if (city == 0 || city == 2) {
 timeZone = AUS_CENTRAL(city,day,month,timeUTC);
 } else if (city == 3 || city == 6 || city == 8 || city == 10) {
 timeZone = AUS_EAST(city, day, month, timeUTC);
 } else {
 timeZone = ISLAND(day, month, timeUTC);
 }

 //take in time zone and timeUTC to work out 24hrs time in function hour_24_format
 localTime = hour_24_format(timeUTC, timeZone);

 return localTime;
}

int hour_24_format(int hour, int zone) {
 int formatted, min;
 min = (hour%100+zone%100)%60;
 formatted = min + 100*((hour / 100 + zone / 100) % 24 + (hour % 100 + zone % 100) / 60);
 return formatted;
}

int NZ(int day, int month, int timeUTC) {

 int timeZone, localTime;

 if (month >= 10) {
 timeZone = TIMEZONE_NZDT;
 } else if (month <= 3) {
 timeZone = TIMEZONE_NZDT;
 } else if (month == 4) {
 localTime = timeUTC + TIMEZONE_NZDT;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC,TIMEZONE_NZDT);
 if (day == 2) {
 if (localTime < 300) {
 timeZone = TIMEZONE_NZDT;
 } else {
 timeZone = TIMEZONE_NZST;
 }
 } else if (day < 2) {
 timeZone = TIMEZONE_NZDT;
 } else {
 timeZone = TIMEZONE_NZST;
 }
 } else if (month == 9) {
 localTime = timeUTC + TIMEZONE_NZST;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC, TIMEZONE_NZST);
 if (day == 24) {
 if (localTime < 200) {
 timeZone=TIMEZONE_NZST;
 } else {
 timeZone=TIMEZONE_NZDT;
 }
 } else if (day<24) {
 timeZone=TIMEZONE_NZST;
 } else {
 timeZone=TIMEZONE_NZDT;
 }
 } else {
 timeZone=TIMEZONE_NZST;}

 return timeZone;
}

int AUS_NODAYLIGHT (int city, int day, int month, int timeUTC){

 int timeZone;
 if (city == 1) {
 timeZone = TIMEZONE_AEST;
 } else if (city == 4) {
 timeZone = TIMEZONE_ACST;
 } else if (city == 5) {
 timeZone = TIMEZONE_ACWST;
 } else {
 timeZone = TIMEZONE_AWST;
 }

 return timeZone;
}

int AUS_CENTRAL(int city, int day, int month, int timeUTC){

 int timeZone, localTime;

 if (month >= 10) {
 timeZone = TIMEZONE_ACDT;
 } else if (month <= 3) {
 timeZone = TIMEZONE_ACDT;
 } else if (month==4) {
 localTime = timeUTC + TIMEZONE_ACDT;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC, TIMEZONE_ACDT);
 if (day == 2) {
 if (localTime < 300) {
 timeZone = TIMEZONE_ACDT;
 } else {
 timeZone = TIMEZONE_ACST;
 }
 } else if (day < 2) {
 timeZone=TIMEZONE_ACDT;
 } else {
 timeZone = TIMEZONE_ACST;
 }
 } else if (month == 9) {
 localTime = timeUTC + TIMEZONE_ACST;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC, TIMEZONE_ACST);
 if (day == 31) {
 if (localTime < 200) {
 timeZone = TIMEZONE_ACST;
 } else {
 timeZone = TIMEZONE_ACDT;
 }
 } else {
 timeZone = TIMEZONE_ACST;
 }
 } else {
 timeZone = TIMEZONE_ACST;
 }

 return timeZone;

}

int AUS_EAST(int city, int day, int month, int timeUTC){

 int timeZone, localTime;

 if (month >= 10) {
 timeZone = TIMEZONE_AEDT;
 } else if (month <= 3) {
 timeZone = TIMEZONE_AEDT;
 } else if (month == 4) {
 localTime = timeUTC + TIMEZONE_AEDT;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC, TIMEZONE_AEDT);
 if (day == 2) {
 if(localTime < 300) {
 timeZone = TIMEZONE_AEDT;
 } else {
 timeZone = TIMEZONE_AEST;
 }
 } else if (day < 2) {
 timeZone = TIMEZONE_AEDT;
 } else {
 timeZone = TIMEZONE_AEST;
 }
 } else if (month == 9) {
 localTime = timeUTC + TIMEZONE_AEST;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC, TIMEZONE_AEST);
 if (day==31) {
 if(localTime < 200) {
 timeZone = TIMEZONE_AEST;
 } else {
 timeZone = TIMEZONE_AEDT;
 }
 } else {
 timeZone = TIMEZONE_AEST;
 }
 } else {
 timeZone = TIMEZONE_AEST;
 }

 return timeZone;
}

int ISLAND(int day, int month, int timeUTC){

 int timeZone, localTime;

 if (month >= 10) {
 timeZone = TIMEZONE_LHDR;
 } else if (month <= 3) {
 timeZone=TIMEZONE_LHDR;
 } else if (month == 4) {
 localTime = timeUTC + TIMEZONE_LHDR;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC, TIMEZONE_LHDR);
 if (day == 2) {
 if (localTime < 200) {
 timeZone = TIMEZONE_LHDR;
 } else {
 timeZone=TIMEZONE_LHST;
 }
 } else if (day < 2) {
 timeZone = TIMEZONE_LHDR;
 } else {
 timeZone = TIMEZONE_LHST;
 }
 } else if (month == 9) {
 localTime = timeUTC + TIMEZONE_LHST;
 if (localTime / 2400) {
 day++;
 }
 localTime = hour_24_format(timeUTC, TIMEZONE_LHST);
 if (day == 31) {
 if (localTime < 200) {
 timeZone = TIMEZONE_LHST;
 } else {
 timeZone = TIMEZONE_LHDR;
 }
 } else {
 timeZone = TIMEZONE_LHST;
 }
 } else {
 timeZone = TIMEZONE_LHST;
 }

 return timeZone;

}




