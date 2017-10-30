// localTime.c
// A program to test a function getLocalTime which determines the
// local time in a specified city, given the current UTC time.
//
// This program by Kanadech Jirapongtanavech (z5176970) on 2017-08-16
//
// Program stub created by Andrew Bennett on 2017-08-01.
// Version 1.0.5: Fix typo in Lord Howe Daylight Time.
// Version 1.0.4: Fix incorrect Lord Howe Island unit test.
// Version 1.0.3: Add version numbers.
// Version 1.0.2: Fixed include order.
// Version 1.0.1: Fix `CITY_LORD_HOWE_IS` symbol name.
// Version 1.0.0: First release onto an unsuspecting class.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE !TRUE

// ===========      Cities      ===========

// Australia
#define CITY_ADELAIDE       0
#define CITY_BRISBANE       1
#define CITY_BROKEN_HILL    2
#define CITY_CANBERRA       3
#define CITY_DARWIN         4
#define CITY_EUCLA          5
#define CITY_HOBART         6
#define CITY_LORD_HOWE_IS   7
#define CITY_MELBOURNE      8
#define CITY_PERTH          9
#define CITY_SYDNEY         10

// New Zealand
#define CITY_AUCKLAND       11
#define CITY_CHRISTCHURCH   12
#define CITY_WELLINGTON     13

// =========== Timezone Offsets ===========

// Australia
#define TIMEZONE_AWST 800 // Australian Western Standard Time

#define TIMEZONE_ACWST 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST  930 // Australian Central Standard Time
#define TIMEZONE_ACDT 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST 1200 // NZ Standard Time
#define TIMEZONE_NZDT 1300 // NZ Daylight Time


// =========== Function Prototypes ===========
//       [DO NOT CHANGE THIS PROTOTYPE!]
int getLocalTime (int city, int day, int month, int timeUTC);
int newZealandCities (int day, int month, int timeUTC);
int AUS_NODAYLIGHT (int city, int day, int month, int timeUTC);
int AUS_CENTRAL (int city, int day, int month, int timeUTC);
int AUS_EAST (int city, int day, int month, int timeUTC);
int lordH_Island (int day, int month, int timeUTC);
int timeIn24HrsFormat (int hour,int zone);

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

    // Add your own tests here

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

    // UTC time: 4:00 pm on 1st April, time in in Sydney: 2:00am on the 2nd
    assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);

    // UTC time: 3:59 pm on 1st April, time in in Sydney: 2:59am on the 2nd
    assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);

    // UTC time: 4:00 pm on 30th September, time in in Adelaide: 3:00am on the 1st
    assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);

    // UTC time: 3:59 pm on 30th September, time in in Adelaide: 1:59am on the 1st
    assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);

    // UTC time: 5:59am on 4th April, time in Eucla: 2:44pm
    assert(getLocalTime(CITY_EUCLA, 4, 4, 559) == 1444);

    // UTC time: 3:59pm on 30th September, time in Sydney: 1:59am
    assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);

    // UTC time: 4:00pm on 30th September, time in Sydney: 3:00am
    assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);

    // UTC time: 3:30pm on 30th September, time in Sydney: 2:30am
    assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9,1530) == 230);

    // UTC time: 5:55pm on 13th November, time in Sydney: 4:55 am
    assert(getLocalTime(CITY_SYDNEY, 13, 11, 1755) == 455);

    // UTC time: 4:30am on 3rd April, time in Brisbane: 2:30 pm
    assert(getLocalTime(CITY_BRISBANE, 3, 4, 430) == 1430);

    // UTC time: 9:10pm on 3rd April, time in Wellington: 9:10 am
    assert(getLocalTime(CITY_WELLINGTON, 3, 4, 2110) == 910);

// ========== Tests shared by users from webcms ===========

// UTC time: 8:05 am on 4th October, time in Eucla: 4:50pm
assert(getLocalTime(CITY_EUCLA, 4, 10, 805) == 1650);
// UTC time: 8:15 am on 4th October, time in Eucla: 5:00pm
assert(getLocalTime(CITY_EUCLA, 4, 10, 815) == 1700);
// UTC time: 8:25 am on 4th October, time in Eucla: 5:10pm
assert(getLocalTime(CITY_EUCLA, 4, 10, 825) == 1710);
// UTC time: 2pm on 1st April, time in Auckland: 2am
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1400) == 200);
// UTC time: 159pm on 1st April, time in Auckland: 259am
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1359) == 259);
// UTC time: 12:00am on 25th November, time in Sydney: 11:00 am
assert(getLocalTime(CITY_SYDNEY, 25, 11, 0) == 1100);
// UTC time: 12:00am on 25th August, time in Sydney: 10:00 am
assert(getLocalTime(CITY_SYDNEY, 25, 8, 0) == 1000);
// UTC time: 9:04pm on 5th August, time in Sydney: 7:04 am
assert(getLocalTime(CITY_SYDNEY, 5, 8, 2104) == 704);
// UTC time: 3:15 pm on 5th September, time in Eucla: 12:00 am
//assert(getLocalTime(CITY_EUCLA, 5, 9, 1515) == 0);
/// UTC time: 12:00 am on 6th Oct, time in Christchurch: 1:00 pm
// on the 7th
assert(getLocalTime(CITY_CHRISTCHURCH, 6, 10, 0) == 1300);
// UTC time: 5pm on 1st April, time in Sydney: 3am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1700) == 300);
// UTC time: 4:59pm on 1st April, time in Sydney: 2:59am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1659) == 259);
// UTC time: 5:01pm on 1st April, time in Sydney: 3:01am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1701) == 301);
// UTC time: 3pm on 1st April, time in Sydney: 2:00am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1500) == 200);
// UTC time: 2:59pm on 1st April, time in Sydney: 1:59am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1459) == 159);
// UTC time: 3:01pm on 1st April, time in Sydney: 2:01am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1501) == 201);
// UTC time: 16:30pm on 30th September, time in Adelaide: 3:00am
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1630) == 300);
// UTC time: 16:29pm on 30th September, time in Adelaide: 1:59am
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1629) == 159);
// UTC time: 13:01pm on 1st April, time in Auckland: 2:00am
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1301) == 201);
// UTC time: 14:01pm on 1st April, time in Auckland: 2:00am
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1401) == 201);
// UTC time: 00:01am on 1st January, time in Perth: 8:00am on
// the 1st
assert(getLocalTime(CITY_PERTH, 1, 1, 0001) == 801);
//UTC time: 00:01am on 1st December, time in Perth: 7:11am on
// the 1st
assert(getLocalTime(CITY_PERTH, 1, 12, 0001) == 801);
//UTC time: 00:01am on 1st June, time in Perth: 7:11am on the 1st
assert(getLocalTime(CITY_PERTH, 1, 6, 0001) == 801);
// UTC time: 00:01am on 1st January, time in Eucla: 8:46am on
// the 1st
assert(getLocalTime(CITY_EUCLA, 1, 1, 0001) == 846);
//UTC time: 00:01am on 1st December, time in Eucla: 8:46am
// on the 1st
assert(getLocalTime(CITY_EUCLA, 1, 12, 0001) == 846);
//UTC time: 00:01am on 1st June, time in Eucla: 8:46am on the 1st
assert(getLocalTime(CITY_EUCLA, 1, 6, 0001) == 846);
//UTC time: 00:01am on 1st June, time in Adelaide: 8:46am
// on the 1st
assert(getLocalTime(CITY_ADELAIDE, 1, 6, 0001) == 931);
// UTC time 4:29pm on 1st April, time in Adelaide: 2:59am
// on the 2nd
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1629) == 259);
// UTC time 4:30pm on 1st April, time in Adelaide: 2am on the 2nd
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1630) == 200);
// UTC time: 2:59pm on 30th September, time in Adelaide: 00:29am
//assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1459) == 29);
// UTC time: 4:29pm on 30th September, time in Adelaide: 1:59am
// on the 1st
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1629) == 159);
// UTC time: 4:30pm on 30th September, time in Adelaide: 3am
// on the 1st
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1630) == 300);
// UTC time: 00:01am on 1st January, time in Darwin: 9:31am
// on the 1st
assert(getLocalTime(CITY_DARWIN, 1, 1, 0001) == 931);
//UTC time: 00:01am on 1st December, time in Darwin: 9:31am
//on the 1st
assert(getLocalTime(CITY_DARWIN, 1, 12, 0001) == 931);
//UTC time: 00:01am on 1st June, time in Darwin: 9:31am on the 1st
assert(getLocalTime(CITY_DARWIN, 1, 6, 0001) == 931);
// UTC time: 3:59pm on 1st April, time in Sydney: 2:59am on the 1st
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 4pm on 1st April, time in Sydney: 2am on the 1st
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
// UTC time: 3:59pm on 30th September, time in Sydney: 1:59am
// on the 1st
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
// UTC time: 4pm on 30th September, time in Sydney: 3am on the 1st
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 2pm on 18th April, time in Brisbane: 12:00am
// on the 19th
assert(getLocalTime(CITY_BRISBANE, 18, 4, 1400) == 0);
// UTC time: 11:06am on 8th October, time in Brisbane: 9:06pm
assert(getLocalTime(CITY_BRISBANE, 8, 10, 1106) == 2106);
// UTC time: 8:15pm on 17th August, time in Brisane: 6:15am
assert(getLocalTime(CITY_BRISBANE, 17, 8, 2015) == 615);
// UTC time: 00:01am on 1st June, time in Sydney: 10:01am
// on the 1st
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 6, 1) == 1031);
// UTC time: 2:59pm on 1st April, time in Lord Howe Island: 1:59am
// on the 1st
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1459) == 159);
// UTC time: 3pm on 1st April, time in Lord Howe Island: 1:30am
// on the 2nd
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
// UTC Time: 1:31pm on 1st of April, time in Lord Howe IS: 00:31am
// on the 2nd
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1331) == 31);
// UTC time: 3:29pm on 30th September, time in Lord Howe Island:
// 1:59am on the 1st Oct
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1529) == 159);
// UTC time: 3:30pm on 30th September, time in Lord Howe Island:
// 2:30am on the 1st Oct
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
// UTC time: 1:59pm on 30th September, time in Lord Howe Island:
// 00:29am on the 1st Oct
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1359) == 29);
// UTC time: 00:01am on 1st June, time in Sydney: 12:01pm
// on the 1st
assert(getLocalTime(CITY_AUCKLAND, 1, 6, 1) == 1201);
// UTC time: 1:59pm on 1st April, time in Auckland: 2:59am on
// the 1st
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1359) == 259);
// UTC time: 2pm on 1st April, time in Auckland: 2am on the 1st
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1400) == 200);
// UTC time: 2pm on 24th September, time in Auckland: 3am
// on the 24th
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1400) == 300);
// UTC time: 1:59pm on 24th September, time in Auckland:
// 1:59am on the 25th
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1359) == 159);
// UTC time: 1:20am on 3rd March, time in Sydney: 12:20 pm
assert(getLocalTime(CITY_SYDNEY, 3, 3, 120) == 1220);
//UTC time: 6:01am on 6th May, time in Melbourne: 4:01 pm
assert(getLocalTime(CITY_MELBOURNE, 6, 5, 601) == 1601);
// UTC time: 12:18 pm on 25th August, time in Sydney: 10:18 pm
assert(getLocalTime(CITY_SYDNEY, 25, 8, 1218) == 2218);
// UTC time: 06:59pm on 30th Sep, time in Eucla: 2:44 am
assert(getLocalTime(CITY_EUCLA, 30, 9, 1859) == 344);
// UTC time: 5:15pm on 30th Sep, time in Eucla: 3;00 am
assert(getLocalTime(CITY_EUCLA, 30, 9, 1715) == 200);
// UTC time: 10:55pm on 1st Apr, time in Lord Howe Island
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1055) == 2155);
// UTC time: 16:31pm on 1st Apr, time in Lord Howe Island
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1631) == 301);
// UTC time: 16:29pm on 1st Apr, time in Lord Howe Island
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1629) == 259);
// UTC time: 12:35pm on 6th May, time in Sydney: 10:35pm
assert(getLocalTime(CITY_SYDNEY, 5, 6, 1235) == 2235);
// UTC time: 2pm on 7th June, time in Sydney: 12am
assert(getLocalTime(CITY_SYDNEY, 7, 8, 1400) == 0);
// UTC time: 12:01 am on 1st January, time in Christchurch: 1:01 pm
assert(getLocalTime(CITY_CHRISTCHURCH, 1, 1, 0001) == 1301);
// UTC time: 10:59 am on 31st December, time in Christchurch:
// 11:59 pm
assert(getLocalTime(CITY_CHRISTCHURCH, 31, 12, 1059) == 2359);
// UTC time: 12:01 am on 1st January, time in Hobart: 11:01 am
assert(getLocalTime(CITY_HOBART, 1, 1, 0001) == 1101);
// UTC time: 12:59 pm on 31st December, time in Hobart: 11:59 pm
assert(getLocalTime(CITY_HOBART, 31, 12, 1259) == 2359);
// UTC time: 8:00am on 22nd October, time in Brisbane: 6:00pm
assert(getLocalTime(CITY_BRISBANE, 22, 10, 800) == 1800);
// UTC time: 8:56am on 25th August, time in Eucla: 5:41pm
assert(getLocalTime(CITY_EUCLA, 25, 8, 856) == 1741);
// UTC time: 3:58pm on 30th September, time in Eucla: 12:43am
assert(getLocalTime(CITY_EUCLA, 30, 9, 1558) == 43);
// UTC time: 3:45pm on 30th September, time in Eucla: 12:30am
assert(getLocalTime(CITY_EUCLA, 30, 9, 1545) == 30);
// UTC time: 11:59pm on 31st December, time in Auckland: 12:59pm
assert(getLocalTime(CITY_AUCKLAND, 31, 12, 2359) == 1259);
// UTC time: 9:00am on 28th August, time in Sydney: 7:00pm
assert(getLocalTime(CITY_SYDNEY, 28, 8, 900) == 1900);
// UTC time: 2:33pm on 13th March, time in Lord Howe Island: 1:33am
assert(getLocalTime(CITY_LORD_HOWE_IS, 13, 3, 1433) == 133);
// UTC time: 10:45am on 21th July, time in Canberra: 8:45 pm
assert(getLocalTime(CITY_CANBERRA, 20, 7, 1005) == 2005);
// UTC time: 9:05am on 20th July, time in Sydney: 7:05 pm
assert(getLocalTime(CITY_SYDNEY, 20, 7, 905) == 1905);
// UTC time: 3:59pm on 30th September, time in Sydney: 1:59am
// on the 1st
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
// UTC time: 4:00pm on 30th September, time in Sydney: 3:00am
// on the 1st
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 3:59pm on 1st April, time in Sydney: 2:59am on the 2nd
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April, time in Sydney: 2:00am on the 2nd
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
// UTC time: 4.30pm on 30 Sept, time in Adelaide: 3.00am;
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1630) == 300);
// UTC time: 11:59pm on 6th April, time in Eucla: 8:44am on the
// 7th my test
assert(getLocalTime(CITY_EUCLA, 6, 4, 2359) == 844);
// UTC time: 11:00pm on 6th April, time in Eucla: 7:45am on the
// 7th my test
assert(getLocalTime(CITY_EUCLA, 6, 4, 2300) == 745);
// UTC time: midnight on 1th April, time in Sydney: 10am my test
assert(getLocalTime(CITY_SYDNEY, 1, 4, 0) == 1100);
// UTC time: 10:30am on 30th June, time in Adelaide: 8pm my test
assert(getLocalTime(CITY_ADELAIDE, 30, 1, 1030) == 2100);
// UTC time: 10:30am on 30th June, time in Adelaide: 8pm my test
assert(getLocalTime(CITY_ADELAIDE, 30, 1, 1029) == 2059);
// UTC time: 3:59am on 22nd September, time in Auckland: 3:59pm
assert(getLocalTime(CITY_AUCKLAND, 22, 9, 359) == 1559);
// UTC time: 3:00am on 24nd September, time in Christchurch: 4:00pm
assert(getLocalTime(CITY_CHRISTCHURCH, 24, 9, 300) == 1600);
//DST start boundary check
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1601) == 301);
//DST end boundary check
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1601) == 201);
//Random time boundary check
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1537) == 137);
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1509) == 109);
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1623) == 223);
// Some unit tests for the timezone borders of Adelaide.
// UTC time: 4:29pm on 1st April, time in Adelaide: 2:59am
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1629) == 259);
// UTC time: 4:30pm on 1st April, time in Adelaide: 2:00am
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1630) == 200);
// UTC time: 4:31pm on 1st April, time in Adelaide: 2:01am
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1631) == 201);
// UTC time: 4:29pm on 30th September, time in Adelaide: 1:59am
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1629) == 159);
// UTC time: 4:30pm on 30th September, time in Adelaide: 3:00am
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1630) == 300);
// UTC time: 4:31pm on 30th September, time in Adelaide: 3:01am
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1631) == 301);
// UTC time: 12:00am on 1st January, time in Adelaide: 10.30am
assert(getLocalTime(CITY_ADELAIDE, 1, 1, 0) == 1030);
// UTC time: 1:29pm on 31st December, time in Adelaide: 11:59pm
assert(getLocalTime(CITY_ADELAIDE, 31, 12, 1329) == 2359);
// UTC time: 3:16pm on 31st December, time in Eucla: 12:01am on
// the 1st of January
assert(getLocalTime(CITY_EUCLA, 31, 12, 1516) == 1);
// UTC time 11:57pm on 1st October, time in Broken Hill 10:27 am
assert(getLocalTime(CITY_BROKEN_HILL, 1, 10, 2357) == 1027);
// UTC time: 1:43pm on 23th April, time in Wellington: 1:43 am
assert(getLocalTime(CITY_WELLINGTON, 23, 4, 1343) == 143);
// UTC time: 9:59pm on 1st April, time in Christchurch: 9:59am on
// the 2nd
assert(getLocalTime(CITY_CHRISTCHURCH, 1, 4, 2159) == 959);
// UTC time: 7:57pm on 30th August, time in Lord Howe Island:
// 6:27am on the 31st
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 8, 1957) == 627);
// UTC time: 9:35pm on 31st December, time in Eucla: 6:20am on
// the 1st of January
assert(getLocalTime(CITY_EUCLA, 31, 12, 2135) == 620);
// UTC time: 12.00 on 6th September time in Brisbane: 10:00 pm
assert(getLocalTime(CITY_BRISBANE, 6, 9, 1200) == 2200);
// UTC time: 4:00pm on 30th September, time in Sydney: 3:00am on
// 1st Oct (clocks move forward 1 hour)
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 5.00pm on 1st April, time in Sydney: 3:00am on
// 2nd April (clocks move back one hour)
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1700) == 300);
// UTC time: 10.00 on 1st October time in Sydney: 9:00 am
assert(getLocalTime(CITY_SYDNEY, 1, 10, 2200) == 900);
// UTC time: midnight on 6th February, time in Eucla: 8:45am
assert(getLocalTime(CITY_EUCLA, 6, 2, 0) == 845);
// UTC time: 12:02am on 6th February, time in Eucla: 8:47am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2) == 847);
// UTC time: 12:04am on 6th February, time in Eucla: 8:49am
assert(getLocalTime(CITY_EUCLA, 6, 2, 4) == 849);
// UTC time: 12:08am on 6th February, time in Eucla: 8:53am
assert(getLocalTime(CITY_EUCLA, 6, 2, 8) == 853);
// UTC time: 12:16am on 6th February, time in Eucla: 9:01am
assert(getLocalTime(CITY_EUCLA, 6, 2, 16) == 901);
// UTC time: 12:32am on 6th February, time in Eucla: 9:17am
assert(getLocalTime(CITY_EUCLA, 6, 2, 32) == 917);
// UTC time: 12:00pm on 6th February, time in Eucla: 8:45pm
assert(getLocalTime(CITY_EUCLA, 6, 2, 1200) == 2045);
// UTC time: 10:00pm on 6th February, time in Eucla: 6:45am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2200) == 645);
// UTC time: 11:00pm on 6th February, time in Eucla: 7:45am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2300) == 745);
// UTC time: 11:10pm on 6th February, time in Eucla: 7:55am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2310) == 755);
// UTC time: 11:20pm on 6th February, time in Eucla: 8:05am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2320) == 805);
// UTC time: 11:30pm on 6th February, time in Eucla: 8:15am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2330) == 815);
// UTC time: 11:40pm on 6th February, time in Eucla: 8:25am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2340) == 825);
// UTC time: 11:50pm on 6th February, time in Eucla: 8:35am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2350) == 835);
// UTC time: 11:51pm on 6th February, time in Eucla: 8:36am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2351) == 836);
// UTC time: 11:52pm on 6th February, time in Eucla: 8:37am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2352) == 837);
// UTC time: 11:53pm on 6th February, time in Eucla: 8:38am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2353) == 838);
// UTC time: 11:54pm on 6th February, time in Eucla: 8:39am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2354) == 839);
// UTC time: 11:55pm on 6th February, time in Eucla: 8:40am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2355) == 840);
// UTC time: 11:56pm on 6th February, time in Eucla: 8:41am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2356) == 841);
// UTC time: 11:57pm on 6th February, time in Eucla: 8:42am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2357) == 842);
// UTC time: 11:58pm on 6th February, time in Eucla: 8:43am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2358) == 843);
// UTC time: 11:59pm on 6th February, time in Eucla: 8:44am
assert(getLocalTime(CITY_EUCLA, 6, 2, 2359) == 844);
// UTC time: 4:30pm on 1st April, time in Sydney: 2:30 am on
// the 2nd of April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1630) == 230);
// UTC time: 17:00 on 1st of April, time in Hobart: 3:00
assert(getLocalTime(CITY_HOBART, 1, 4, 1700) == 300);
// UTC time: 3:30pm on 24th August, time in Lord Howe Island:
// 2:00am on the 25th
assert(getLocalTime(CITY_LORD_HOWE_IS, 24, 8, 1530) == 200);
// UTC time: 11:49pm on 1st January, time in Eucla: 8:34am on
// the 2nd
assert(getLocalTime(CITY_EUCLA, 1, 1, 2349) == 834);
// UTC time: 9:22pm on 30th September, time in Christchurch:
// 10:22am on the 1st of October
assert(getLocalTime(CITY_CHRISTCHURCH, 30, 9, 2122) == 1022);
// UTC time: 3:57pm on 25th June, time in Eucla: 12:42am
// on the 26th
assert(getLocalTime(CITY_EUCLA, 25, 6, 1557) == 42);
// UTC time: 1:59pm on 24th September, time in Christchurch:
// 1:59am on the 25th
assert(getLocalTime(CITY_CHRISTCHURCH, 23, 9, 1359) == 159);
// UTC time: 2pm on 24th September, time in Christchurch: 3am
// on the 25th
assert(getLocalTime(CITY_CHRISTCHURCH, 23, 9, 1400) == 300);
// UTC time: 3:59pm on 30th September, time in Canberra: 1:59am
// on the 1st
assert(getLocalTime(CITY_CANBERRA, 30, 9, 1559) == 159);
// UTC time: 4:01pm on 30th September, time in Canberra: 3:01am
// on the 1st
assert(getLocalTime(CITY_CANBERRA, 30, 9, 1601) == 301);
// UTC time: 2:59pm on 1st April, time in Lord Howe Island: 1:45am
// on the 2nd
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1459) == 159);
// UTC time: 3pm on 1st April, time in Lord Howe Island: 1:30am
// on the 2nd
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
// UTC time 4:29pm on 1st April, time in Broken Hill: 2:59am
// on the 2nd
assert(getLocalTime(CITY_BROKEN_HILL, 1, 4, 1629) == 259);
// UTC time 4:30pm on 1st April, time in Broken Hill: 2am
// on the 2nd
assert(getLocalTime(CITY_BROKEN_HILL, 1, 4, 1630) == 200);
//UTC time: 11:30 pm on 7th September, time in Auckland: 11:30 am
assert(getLocalTime(CITY_AUCKLAND, 7, 9, 2330) == 1130);
//UTC time: 11:30 pm on 7th December, time in Eucla: 8:20 am
assert(getLocalTime(CITY_EUCLA, 7, 10, 2335) == 820);
//UTC time: 3:00pm on 1st April, time in Lord Howie Island: 1:30am
assert (getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
//UTC time 12:50pm on 1st April, time in Lord Howie Island: 11:50pm
assert (getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1250) == 2350);
// UTC time: 3:59pm on 1st April,
// time in Canberra: 2:59am on 2nd April
assert(getLocalTime(CITY_CANBERRA, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April,
// time in Canberra: 2:00am on 2nd April
assert(getLocalTime(CITY_CANBERRA, 1, 4, 1600) == 200);
// UTC time: 3:59pm on 30th September,
// time in Canberra: 1:59am on 1st October
assert(getLocalTime(CITY_CANBERRA, 30, 9, 1559) == 159);
// UTC time: 4:00pm on 30th September,
// time in Canberra: 3:00am on 1st October
assert(getLocalTime(CITY_CANBERRA, 30, 9, 1600) == 300);
// UTC time: 3:59pm on 1st April,
// time in Hobart: 2:59am on 2nd April
assert(getLocalTime(CITY_HOBART, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April,
// time in Hobart: 2:00am on 2nd April
assert(getLocalTime(CITY_HOBART, 1, 4, 1600) == 200);
// UTC time: 3:59pm on 30th September,
// time in Hobart: 1:59am on 1st October
assert(getLocalTime(CITY_HOBART, 30, 9, 1559) == 159);
// UTC time: 4:00pm on 30th September,
// time in Hobart: 3:00am on 1st October
assert(getLocalTime(CITY_HOBART, 30, 9, 1600) == 300);
// UTC time: 3:59pm on 1st April,
// time in Melbourne: 2:59am on 2nd April
assert(getLocalTime(CITY_MELBOURNE, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April,
// time in Melbourne: 2:00am on 2nd April
assert(getLocalTime(CITY_MELBOURNE, 1, 4, 1600) == 200);
// UTC time: 3:59pm on 30th September,
// time in Melbourne: 1:59am on 1st October
assert(getLocalTime(CITY_MELBOURNE, 30, 9, 1559) == 159);
// UTC time: 4:00pm on 30th September,
// time in Melbourne: 3:00am on 1st October
assert(getLocalTime(CITY_MELBOURNE, 30, 9, 1600) == 300);
// UTC time: 3:59pm on 1st April,
// time in Sydney: 2:59am on 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April,
// time in Sydney: 2:00am on 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
// UTC time: 3:59pm on 30th September,
// time in Sydney: 1:59am on 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
// UTC time: 4:00pm on 30th September,
// time in Sydney: 3:00am on 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 4:29pm on 1st April,
// time in Adelaide: 2:59am on 2nd April
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1629) == 259);
// UTC time: 4:30pm on 1st April,
// time in Adelaide: 2:00am on 2nd April
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1630) == 200);
// UTC time: 4:29pm on 30th September,
// time in Adelaide: 1:59am on 1st October
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1629) == 159);
// UTC time: 4:30pm on 30th September,
// time in Adelaide: 3:00am on 1st October
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1630) == 300);
// UTC time: 4:29pm on 1st April,
// time in Broken Hill: 2:59am on 2nd April
assert(getLocalTime(CITY_BROKEN_HILL, 1, 4, 1629) == 259);
// UTC time: 4:30pm on 1st April,
// time in Broken Hill: 2:00am on 2nd April
assert(getLocalTime(CITY_BROKEN_HILL, 1, 4, 1630) == 200);
// UTC time: 4:29pm on 30th September,
// time in Broken Hill: 1:59am on 1st October
assert(getLocalTime(CITY_BROKEN_HILL, 30, 9, 1629) == 159);
// UTC time: 4:30pm on 30th September,
// time in Broken Hill: 3:00am on 1st October
assert(getLocalTime(CITY_BROKEN_HILL, 30, 9, 1630) == 300);
// UTC time: 2:59pm on 1st April,
// time in Lord Howe Island: 1:59am on 2nd April
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1459) == 159);
// UTC time: 3:00pm on 1st April,
// time in Lord Howe Island: 1:30am on 2nd April
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
// UTC time: 3:29pm on 30th September,
// time in Lord Howe Island: 1:59am on 1st October
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1529) == 159);
// UTC time: 3:30pm on 30th September,
// time in Lord Howe Island: 2:30am on 1st October
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
// UTC time: 1:59pm on 1st April,
// time in Auckland: 2:59am on 2nd April
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1359) == 259);
// UTC time: 2:00pm on 1st April,
// time in Auckland: 2:00am on 2nd April
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1400) == 200);
// UTC time: 1:59pm on 24th September,
// time in Auckland: 1:59am on 25th September
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1359) == 159);
// UTC time: 2:00pm on 24th September,
// time in Auckland: 3:00am on 25th September
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1400) == 300);
// UTC time: 1:59pm on 1st April,
// time in Christchurch: 2:59am on 2nd April
assert(getLocalTime(CITY_CHRISTCHURCH, 1, 4, 1359) == 259);
// UTC time: 2:00pm on 1st April,
// time in Christchurch: 2:00am on 2nd April
assert(getLocalTime(CITY_CHRISTCHURCH, 1, 4, 1400) == 200);
// UTC time: 1:59pm on 24th September,
// time in Christchurch: 1:59am on 25th September
assert(getLocalTime(CITY_CHRISTCHURCH, 23, 9, 1359) == 159);
// UTC time: 2:00pm on 24th September,
// time in Christchurch: 3:00am on 25th September
assert(getLocalTime(CITY_CHRISTCHURCH, 23, 9, 1400) == 300);
// UTC time: 1:59pm on 1st April,
// time in Wellington: 2:59am on 2nd April
assert(getLocalTime(CITY_WELLINGTON, 1, 4, 1359) == 259);
// UTC time: 2:00pm on 1st April,
// time in Wellington: 2:00am on 2nd April
assert(getLocalTime(CITY_WELLINGTON, 1, 4, 1400) == 200);
// UTC time: 1:59pm on 24th September,
// time in Wellington: 1:59am on 25th September
assert(getLocalTime(CITY_WELLINGTON, 23, 9, 1359) == 159);
// UTC time: 2:00pm on 24th September,
// time in Wellington: 3:00am on 25th September
assert(getLocalTime(CITY_WELLINGTON, 23, 9, 1400) == 300);
// UTC time: 2:59pm on 30th September,
// time in Adelaide: 12:29am on 1st October
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1459) == 29);
// UTC time: 2:59pm on 30th September,
// time in Broken Hill: 12:29am on 1st October
assert(getLocalTime(CITY_BROKEN_HILL, 30, 9, 1459) == 29);
// UTC time: 2:59pm on 30th September,
// time in Darwin: 12:29am on 1st October
assert(getLocalTime(CITY_DARWIN, 30, 9, 1459) == 29);
// UTC time: 3:59pm on 30th September,
// time in Eucla: 12:44am on 1st October
assert(getLocalTime(CITY_EUCLA, 30, 9, 1559) == 44);
// UTC time: 3:54pm on 30th September,
// time in Eucla: 12:39am on 1st October
assert(getLocalTime(CITY_EUCLA, 30, 9, 1554) == 39);
// UTC time: 1:59pm on 30th September,
// time in Lord Howe Island: 12:29am on 1st October
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1359) == 29);
// UTC Time: 1:46pm on 1st of April,
// time in Lord Howe Island: 12:46am on 2nd April
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1346) == 46);
// UTC time: 1:00am on 2nd January, time in Christchurch: 9:45am
assert(getLocalTime(CITY_EUCLA, 2, 1, 100) == 945);
//UTC time: 3:30 pm on 30th September, time in Lord Howe Island:
// 2:30am
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
//UTC time: 3:00 pm on 1st April, time in Lord Howe Island: 1:30am
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
// UTC time: 3:01pm on 1st April, time in Sydney: 2:01 am
// on 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1501) == 201);
// UTC time: 4:01pm on 1st April, time in Sydney: 2:01 am
// on 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1601) == 201);
// UTC time: 5:01pm on 1st April, time in Sydney: 3:01 am
// on 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1701) == 301);
// UTC time: 3:01pm on 30th September, time in Sydney: 1:01 am
// on 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1501) == 101);
// UTC time: 4:01pm on 30th September, time in Sydney: 3:01 am
// on 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1601) == 301);
// UTC time: 5:01pm on 30th September, time in Sydney: 4:01 am
// on 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1701) == 401);
//UTC time: 4:15pm on 30th September, time in Adelaide: 1:45am
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1615) == 145);
//UTC time: 4:30pm on 30th September, time in Adelaide: 3:00am
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1630) == 300);
// UTC time: 11:11am on 11th November, time in Sydney: 10:11pm
assert(getLocalTime(CITY_SYDNEY, 11, 11, 1111) == 2211);
// UTC time: 1:11am on 11th January, time in Lord Howe Island:
// 12:11pm
assert(getLocalTime(CITY_LORD_HOWE_IS, 11, 1, 111) == 1211);
// UTC time: 6:15pm on 13th October, time in Eucla: 3:00am
// on the 14th
assert(getLocalTime(CITY_EUCLA, 13, 10, 1815) == 300);
// UTC time: 15:15 on 20th Dec., time in Darwin: 00:45 am on 21st
assert(getLocalTime(CITY_DARWIN, 20, 12, 1515) == 45);
// UTC time: 15:15 on 31st Jan., time in Lord Howe Island: 2:15 am
// on 1st Feb
assert(getLocalTime(CITY_LORD_HOWE_IS, 31, 1, 1515) == 215);
// UTC time: 16:30 on 30th Sept., time in Sydney: 3:30 am
// on 1st of Oct.
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1630) == 330);
// UTC time: 1:32am on 25th January, time in MELBOURNE: 12:32 am
assert(getLocalTime(CITY_MELBOURNE, 25, 1, 132) == 1232);
//DT
// UTC time: 15:59 pm on 1st April, time in Sydney: 2:59 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 15:59 pm on 1st April, time in Sydney: 1:59 am
assert(getLocalTime(CITY_BRISBANE, 1, 4, 1559) == 159);
// UTC time: 13:59 pm on 1st April, time in Christchurch: 2:59 am
assert(getLocalTime(CITY_CHRISTCHURCH, 1, 4, 1359) == 259);
//ST
// UTC time: 15:59 pm on 4th July, time in Eucla: 12:44 am
assert(getLocalTime(CITY_EUCLA, 4, 7, 1559) == 44);
// UTC time: 15:59 pm on 1st April, time in Sydney: 1:29 am
assert(getLocalTime(CITY_DARWIN, 4, 7, 1559) == 129);
// UTC time: 15:59 pm on 4th July, time in Adelaide: 1:29 am
assert(getLocalTime(CITY_ADELAIDE, 4, 7, 1559) == 129);
// UTC time: 15:59 pm on 4th July, time in Perth: 11:59 pm
assert(getLocalTime(CITY_PERTH, 4, 7, 1559) == 2359);
// UTC time: 15:59 pm on 4th July, time in Lord Howe Island:
// 2:29 am
assert(getLocalTime(CITY_LORD_HOWE_IS, 4, 7, 1559) == 229);
// UTC time: 15:59 pm on 4th July, time in Auckland: 3:59 am
assert(getLocalTime(CITY_AUCKLAND, 4, 7, 1559) == 359);
//NADT AUST
// UTC time: 15:59 pm on 23th September, time in Lord Howe Island:
// 12:15 am
assert(getLocalTime(CITY_LORD_HOWE_IS, 23, 9, 1359) == 29);
// UTC time: 15:59 pm on 23th September, time in Auckland: 1:45 am
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1359) == 159);
//AUDT NZDT
// UTC time: 19:59 pm on 23th September, time in Lord Howe Island:
// 6:29 am
assert(getLocalTime(CITY_LORD_HOWE_IS, 2, 11, 1959) == 659);
// UTC time: 19:59 pm on 2nd November, time in Auckland: 8:59 am
assert(getLocalTime(CITY_AUCKLAND, 2, 11, 1959) == 859);
// UTC time: 19:59 pm on 2nd November, time in Sydney: 6:59 am
assert(getLocalTime(CITY_SYDNEY, 2, 11, 1959) == 659);
// UTC time: 19:59 pm on 2nd November, time in Brisbane: 5:59 am
assert(getLocalTime(CITY_BRISBANE, 2, 11, 1959) == 559);
// UTC time: 19:59 pm on 2nd November, time in Christchurch:
// 8:59 am
assert(getLocalTime(CITY_CHRISTCHURCH, 2, 11, 1959) == 859);
// UTC time: 19:59 pm on 2nd November, time in Eucla: 12:44 am
assert(getLocalTime(CITY_EUCLA, 2, 11, 1559) == 44);
// UTC time: 5:30pm on 26th January, time in Broken Hill:
assert(getLocalTime(CITY_BROKEN_HILL, 26, 1, 1730) == 400);
//UTC time: 1:00 on 30th September, time in Auckland:
assert(getLocalTime(CITY_AUCKLAND, 30, 9, 100) == 1400);
//UTC time: 3:30pm 30th September, time in Lord Howe Island: 2:30am
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
//UTC time: 3:30am on 5th May, time in Sydney: 01:30 pm
assert(getLocalTime(CITY_SYDNEY, 5, 5, 330) == 1330);
//UTC time 5:30am on 1st January, time in Melbourne: 4:30 pm
assert(getLocalTime(CITY_MELBOURNE, 1, 1, 530) == 1630);
// UTC time: 3:39am on 1st December time in Darwin: 1:09pm
assert(getLocalTime(CITY_DARWIN, 1, 12, 339) == 1309);
// UTC time: 7:51pm on 4th May, time in Eucla: 4:36am
assert(getLocalTime(CITY_EUCLA, 4, 5, 1951) == 436);
// UTC time: 3:45pm on 1st April, time in Sydney: 2:45 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1545) == 245);
// UTC time: 3:59pm on 1st April, time in Sydney: 2:59 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April, time in Sydney 2:00 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
// UTC time: 4:01pm on 1st April, time in Sydney 2:01 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1601) == 201);
// UTC time: 4:15pm on 1st April, time in Sydney 2:15 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1615) == 215);
// UTC time: 3:45pm on 30th September, time in Sydney: 1:45 am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1545) == 145);
// UTC time: 3:59pm on 30th September, time in Sydney: 1:59 am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
// UTC time: 4:00pm on 30th September, time in Sydney: 3:00 am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 4:01pm on 30th September, time in Sydney: 3:01 am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1601) == 301);
// UTC time: 4:15pm on 30th September, time in Sydney: 3:15 am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1615) == 315);
// UTC time: 3:59pm on 1st April, time in Sydney: 2:59am on
// 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 4pm on 1st April, time in Sydney: 2am on 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
// UTC time: 4.01pm on 1st April, time in Sydney: 2.01am on
// 2nd April
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1601) == 201);
// UTC time: 3:59pm on 30th September, time in Sydney: 1:59am on
// 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
// UTC time: 4pm on 30th September, time in Sydney: 3am on
// 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 4.01pm on 30th September, time in Sydney: 3.01am on
// 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1601) == 301);
// UTC time: 10:19pm on 12th March, time in Eucla: 7:04am on
// the 13th
assert(getLocalTime(CITY_EUCLA, 12, 3, 2219) == 704);
// UTC time: 4:24am on 25th August, time in Eucla: 1:09pm
assert(getLocalTime(CITY_EUCLA, 25, 8, 424) == 1309);
// UTC time: 11pm on 10th May, time in Eucla: 7:45am on the 11th
assert(getLocalTime(CITY_EUCLA, 10, 5, 2300) == 745);
// UTC time: 12:49pm on 15th January, time in Eucla: 9:34pm
assert(getLocalTime(CITY_EUCLA, 15, 1, 1249) == 2134);
// UTC time: 11:41pm on 30th September, time in Adelaide: 10:11am
// on the 1st October
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 2341) == 1011);
// UTC time: 11:41pm on 1st April, time in Adelaide: 9:11am on
// the 2nd
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 2341) == 911);
// UTC time: 12:20pm on 30th April, time in Adelaide: 9:50pm
assert(getLocalTime(CITY_ADELAIDE, 30, 4, 1220) == 2150);
// UTC time: 1am on 31st July, time in Darwin: 10:30am
assert(getLocalTime(CITY_DARWIN, 31, 7, 100) == 1030);
// UTC time: 10am on 1st December, time in Canberra: 9:00pm
assert(getLocalTime(CITY_CANBERRA, 1, 12, 1000) == 2100);
// UTC time: 11pm on 18th July, time in Melbourne: 9:00am
assert(getLocalTime(CITY_MELBOURNE, 18, 7, 2300) == 900);
// UTC time: 5:30am on 11th May, time in Lord Howe Island: 4:00pm
assert(getLocalTime(CITY_LORD_HOWE_IS, 11, 5, 530) == 1600);
// UTC time: 12pm on 17th June, time in Auckland: 12:00am
assert(getLocalTime(CITY_AUCKLAND, 17, 6, 1200) == 0);
// UTC time: 4:00pm on 1st April, time in Sydney: 2:00 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
// UTC time: 3:00pm on 1st April, time in Sydney: 2:00 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1500) == 200);
// UTC time: 4:00am on 10th October, time in Sydney: 3:00pm
assert(getLocalTime(CITY_SYDNEY, 10, 10, 400) == 1500);
// UTC time: 3:59pm on 1st April, time in Melbourne: 2:59 am
assert(getLocalTime(CITY_MELBOURNE, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April, time in Melbourne: 2:00 am
assert(getLocalTime(CITY_MELBOURNE, 1, 4, 1600) == 200);
// UTC time: 3:58pm on 30th September, time in Hobart: 1:58 am
assert(getLocalTime(CITY_HOBART, 30, 9, 1558) == 158);
// UTC time: 4:00pm 30th September, time in Sydney: 3:00 am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 3:31pm on 2th April, time in Sydney: 2:31 am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1531) == 231);
// UTC time: 5:00pm on 1th April , time in Sydney:3:am on the 2nd
assert(getLocalTime(CITY_SYDNEY,1,4,1700) == 300);
// UTC time: 2:03pm on 31st March, time in Perth:10:03pm
assert (getLocalTime(CITY_PERTH,31,3,1403) == 2203);
// UTC time: 7:00pm on 23th September, time in Auckland:8:00am
// on the 24th
assert (getLocalTime(CITY_AUCKLAND,23,9,1900) == 800);
// UTC time: 8:31pm on 2nd October, time in Adelaide:7:01am on 3rd
assert (getLocalTime(CITY_ADELAIDE,2,10,2031) == 701);
// UTC time:11:30am on 17th May, time in Eucla:8:15pm
assert (getLocalTime(CITY_EUCLA,5,17,1130) == 2015);
// UTC time: 2:30am on 8th August, time in Broken Hill: 12:00 am
assert(getLocalTime(CITY_BROKEN_HILL, 8, 8, 230) == 1200);
// UTC time: 3:40am on 4th April, time in Eucla Hill: 12:25 am
assert(getLocalTime(CITY_EUCLA, 4, 4, 340) == 1225);
// lord howe island daylight saving boundary
//UTC time: 3:00pm on 1st April, time in Lord Howe Island: 1:30am
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
//UTC time: 3:15pm on 30th September, time in Lord Howe Island:
// 1:45am
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1515) == 145);
//UTC time: 3:30pm on 30th September, time in Lord Howe Island:
// 2:30am
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
// UTC time: 2:20pm on 26th Augest, time in Sydney: 00:20am
assert(getLocalTime(CITY_SYDNEY, 26, 8, 1420) == 20);
// UTC time: 7:56pm on 10th October, time in Eucla: 4:41am
// on the 11th
assert(getLocalTime(CITY_EUCLA, 10, 10, 1956) == 441);
//UTC time 4:29pm on 30th September, time in Adelaide: 1:59am
// on the 1st October
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1629) == 159);
//UTC time 4:30pm on 30th September, time in Adelaide: 3:00am
// on the 1st October
assert(getLocalTime(CITY_ADELAIDE,30, 9, 1630) == 300);
//UTC time 4:29pm on 1st April, time in Adelaide: 2:59am
// on the 2nd
assert(getLocalTime(CITY_ADELAIDE, 1, 4, 1629) == 259);
//UTC time 4:30pm on 1st April, time in Adelaide: 2:00am
// on the 2nd
assert(getLocalTime(CITY_ADELAIDE,1, 4, 1630) == 200);
//UTC time 4:30pm on 1st October, time in Adelaide: 3:00am
// on the 2nd
assert(getLocalTime(CITY_ADELAIDE,1, 10, 1630) == 300);
//UTC time 4:29pm on 20th March, time in Adelaide: 2:59am
// on the 21st
assert(getLocalTime(CITY_ADELAIDE, 20, 3, 1629) == 259);
//UTC time 4:29pm on 30th September, time in Broken Hill: 1:59am
// on the 1st October
assert(getLocalTime(CITY_BROKEN_HILL, 30, 9, 1629) == 159);
//UTC time 4:30pm on 30th September, time in Broken Hill: 3:00am
// on the 1st October
assert(getLocalTime(CITY_BROKEN_HILL,30, 9, 1630) == 300);
//UTC time 4:29pm on 1st April, time in Broken Hill: 2:59am
// on the 2nd
assert(getLocalTime(CITY_BROKEN_HILL, 1, 4, 1629) == 259);
//UTC time 4:30pm on 1st April, time in Broken Hill: 2:00am
// on the 2nd
assert(getLocalTime(CITY_BROKEN_HILL,1, 4, 1630) == 200);
//UTC time 1:30pm on the 13th May, time in Wellington: 1:30am
// on the 14th
assert(getLocalTime(CITY_WELLINGTON, 13,5, 1330) == 130);
//UTC time 2:01am on the 1st April, time in Wellington: 3:01pm
assert(getLocalTime(CITY_WELLINGTON, 1,4, 201) == 1501);
//UTC time: 3:29pm on the 30th September, time in Lord Howe Island
// is 1:59am on 1st October
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1529) == 159);
//UTC time: 3:31pm on the 30th September, time in Lord Howe Island
// is 2:31am on 1st October
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1531) == 231);
//UTC time: 3:00pm on the 1st April, time in Lord Howe Island is
// 1:30am on 2nd April
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
//UTC time: 2:59pm on the 1st April, time in Lord Howe Island
// is 1:59am on 2nd April
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1459) == 159);
//UTC time: 4:00pm on the 30th September, time in Sydney is
// 3:00am on 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
//UTC time: 3:59pm on the 30th September, time in Sydney is
// 1:59am on 1st October
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
//UTC time: 4:00pm on the 1st April, time in Sydney is
// 2:00am on 2nd
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
//UTC time: 3:59pm on the 1st April, time in Sydney
// is 2:59am on 2nd
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
//UTC time: 1:59pm on the 1st April, time in Auckland:
// is 2:59am on 2nd
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1359) == 259);
//UTC time: 2:00pm on the 1st April, time in Auckland:
// is 2:00am on 2nd
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1400) == 200);
//UTC time: 2:00pm on the 23rd september, time in Auckland:
// is 3:00am on 24th
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1400) == 300);
//UTC time: 1:59pm on the 23rd september, time in Auckland:
// is 1:59 am on 24th
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1359) == 159);
//UTC time: 2:00pm on the 24th september, time in Auckland:
// is 3:00am on 25th
assert(getLocalTime(CITY_AUCKLAND, 24, 9, 1400) == 300);
//UTC time: 2:00pm on the 22nd september, time in Auckland:
// is 2:00am on 23rd
assert(getLocalTime(CITY_AUCKLAND, 22, 9, 1400) == 200);
// UTC time: 5:30pm on 26th January, time in Broken Hill:
assert(getLocalTime(CITY_BROKEN_HILL, 26, 1, 1730) == 400);
//UTC time: 1:00 on 30th September, time in Auckland:
assert(getLocalTime(CITY_AUCKLAND, 30, 9, 100) == 1400);
// UTC time: 1:59pm on Sunday 27th August; time in Sydney: 11:59pm
assert(getLocalTime(CITY_SYDNEY, 27, 8, 1359) == 2359);
// UTC time: 3:30pm on 1st April, time in Sydney: 2:30am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1530) == 230);
// UTC time: 4:30pm on 1st April, time in Sydney: 2:30am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1630) == 230);
// UTC time: 3:59pm on 1st April, time in Sydney: 2:59am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 4:00pm on 1st April, time in Sydney: 2:00am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);
// UTC time: 2:00pm on 1st April, time in Auckland: 2:00am on
// the 2nd (When clocks change back from daylight saving)
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1400) == 200);
// UTC time: 1:59pm on 1st April, time in Christchurch: 2:59am
// on the 2nd (Just before clocks change back from daylight saving)
assert(getLocalTime(CITY_CHRISTCHURCH, 1, 4, 1359) == 259);
// UTC time: 2:00pm on 23rd September, time in Wellington: 3:00am
// on the 24th (When clocks change for daylight saving)
assert(getLocalTime(CITY_WELLINGTON, 23, 9, 1400) == 300);
// UTC time: 1:59pm on 23rd September, time in Auckland: 1:59am
// on the 24th (Just before clocks change for daylight saving)
assert(getLocalTime(CITY_AUCKLAND, 23, 9, 1359) == 159);
// UTC time: 19:45am on 2th June, time in Lord Howe Island:
// 6:15am on 3rd June
assert(getLocalTime(CITY_LORD_HOWE_IS, 02, 6, 1945) == 615);
//UTC time: 3:30pm on 1st April, time in Sydney: 2:30am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1530) == 230);
//UTC time: 4:30pm on 1st April, time in Sydney: 2:30am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1630) == 230);
// UTC time: 2:59pm on 1st April, time in Lord Howe Island:
// 1:59am on 2nd April
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1459) == 159);
// UTC time: 3pm on 1st April, time in Lord Howe Island:
// 1:30am on 2nd April
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
// UTC time: 3:29pm on 30th Sept, Lord Howe Island: 1:59am
// on 1st Oct
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1529) == 159);
// UTC time: 3:30pm on 30th Sept, time in Lord Howe Island:
// 2:30am on 1st Oct
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
// UTC time: 4pm on 30th September, time in Sydney: 3:00 am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 2:30am on 16th June, time in Broken Hill: 12:00 pm
assert(getLocalTime(CITY_BROKEN_HILL, 16, 6, 230) == 1200);
// UTC time: 12:10am on 3rd January, time in Perth: 8:10 am
assert(getLocalTime(CITY_PERTH, 3, 1, 10) == 810);
// UTC time: 12am on 1st January,, time in Perth: 8am
assert(getLocalTime(CITY_PERTH, 1, 1, 0) == 800);
// UTC time: 1:59pm on 31st December, time in Eucla: 8:44am
assert(getLocalTime(CITY_EUCLA, 31, 12, 2359) == 844);
// 1st of April UTC = 16:30pm --> Adelaide = 2:00am
assert (getLocalTime (CITY_ADELAIDE, 1, 4, 1630) == 200);
// 1st of April UTC = 15:30pm --> Adelaide = 2:00am
assert (getLocalTime (CITY_ADELAIDE, 1, 4, 1530) == 200);
// 30th of September UTC = 16:29pm --> Adelaide = 1:59am
assert (getLocalTime (CITY_ADELAIDE, 30, 9, 1629) == 159);
// 30th of September UTC = 16:30pm --> Adelaide = 3:00am
assert (getLocalTime (CITY_ADELAIDE, 30, 9, 1630) == 300);
// 1st of April UTC = 15:00pm --> Sydney = 2:00am
assert (getLocalTime (CITY_SYDNEY, 1, 4, 1500) == 200);
// 1st of April UTC = 16:00pm --> Sydney = 2:00am
assert (getLocalTime (CITY_SYDNEY, 1, 4, 1600) == 200);
// 30th of September UTC = 15:59pm --> Sydney = 1:59am
assert (getLocalTime (CITY_SYDNEY, 30, 9, 1559) == 159);
// 30th of September UTC = 16:00pm --> Sydney = 3:00am
assert (getLocalTime (CITY_SYDNEY, 30, 9, 1600) == 300);
// 23rd of September UTC = 13:59pm --> Auckland = 1:59am
assert (getLocalTime (CITY_AUCKLAND, 23, 9, 1359) == 159);
// 23rd of September UTC = 14:00pm --> Auckland = 3:00am
assert (getLocalTime (CITY_AUCKLAND, 23, 9, 1400) == 300);
// 1st of April UTC = 13:00pm --> Auckland = 2:00am
assert (getLocalTime (CITY_AUCKLAND, 1, 4, 1300) == 200);
// 1st of April UTC = 14:00pm --> Auckland = 2:00am
assert (getLocalTime (CITY_AUCKLAND, 1, 4, 1400) == 200);
// 1st of April UTC = 14:30pm --> Lord Howe Island = 1:30am
assert (getLocalTime (CITY_LORD_HOWE_IS, 1, 4, 1430) == 130);
// 1st of April UTC = 15:00pm --> Lord Howe Island = 1:30am
assert (getLocalTime (CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
// 30th of September UTC = 15:29pm --> Lord Howe Island = 1:59am
assert (getLocalTime (CITY_LORD_HOWE_IS, 30, 9, 1529) == 159);
// 30th of September UTC = 15:30pm --> Lord Howe Island = 2:30am
assert (getLocalTime (CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
// UTC time : 1:17am on 17th July, time in Sydney: 11:17 am
assert(getLocalTime(CITY_SYDNEY, 17, 7, 117) == 1117);
// UTC time: 1:17am on 17th July, time in Perth: 9:17
assert(getLocalTime(CITY_PERTH, 17, 7, 117) == 917);
// UTC time: 08:06am on 2nd December, time in Brisbane: 7:06pm
assert(getLocalTime(CITY_BRISBANE, 2, 10, 806) == 1806);
// UTC time: 03:01pm on 29th October, time in Sydney: 02:01apm
assert(getLocalTime(CITY_SYDNEY, 29, 10, 1501) == 201);
// Boundary Tests
// UTC time: 2:59pm on 1st April, time in Lord Howe Island:
// 1:59am on the 2nd
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1459) == 159);
// UTC time: 3:00pm on 1st April, time in Lord Howe Island:
// 1:30am on the 2nd
assert(getLocalTime(CITY_LORD_HOWE_IS, 1, 4, 1500) == 130);
// UTC time: 3:30pm on 30th September, time in Lord Howe Island:
// 2:30am on the 1st
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1530) == 230);
// UTC time: 3:29pm on 30th September, time in Lord Howe Island:
// 1:59am on the 1st
assert(getLocalTime(CITY_LORD_HOWE_IS, 30, 9, 1529) == 159);
// UTC time: 3:59pm on 1st April, time in Sydney: 2:59am on the 2nd
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1559) == 259);
// UTC time: 2:00pm on 23rd September, time in Wellington:
// 3:00am on the 24th
assert(getLocalTime(CITY_WELLINGTON, 23, 9, 1400) == 300);
// UTC time: 4:29pm on 30th September, time in Adelaide: 1:59am
// on the 1st
assert(getLocalTime(CITY_ADELAIDE, 30, 9, 1629) == 159);
// UTC time: 4:30pm on 1st April, time in Broken Hill: 2:00am
// on the 2nd
assert(getLocalTime(CITY_BROKEN_HILL, 1, 4, 1630) == 200);
// Normal Tests
// UTC time: 11:59pm on 31st December, time in Darwin: 9:29am
// on the 1st
assert(getLocalTime(CITY_DARWIN, 31, 12, 2359) == 929);
// UTC time: 4:37am on 5th February, time in Eucla: 1:22pm
assert(getLocalTime(CITY_EUCLA, 5, 2, 437) == 1322);
// UTC time: 7:14pm on 29th June, time in Perth: 3:14am on the 30th
assert(getLocalTime(CITY_PERTH, 29, 6, 1914) == 314);
// UTC time: 2:45am on 6th August, time in Brisbane: 12:45pm
assert(getLocalTime(CITY_BRISBANE, 6, 8, 245) == 1245);
// UTC time: 3:54am on 14th September, time in Auckland: 3:54pm
assert(getLocalTime(CITY_AUCKLAND, 14, 9, 354) == 1554);
// UTC time: 11:13am on 28th November, time in Christchurch:
// 12:13am on the 29th
assert(getLocalTime(CITY_CHRISTCHURCH, 28, 11, 1113) == 13);
// UTC time: 3:10pm on 28th February, time in Hobart: 2:10am
// on the 1st
assert(getLocalTime(CITY_HOBART, 28, 2, 1510) == 210);
// UTC time: 5:10pm on 24th April, time in Melbourne: 3:10am
// on the 25th
assert(getLocalTime(CITY_MELBOURNE, 24, 4, 1710) == 310);
// UTC time: 3:14am on 4th May, time in Canberra: 1:14pm
assert(getLocalTime(CITY_CANBERRA, 4, 5, 314) == 1314);
// UTC time: 9:57pm on 30th September, time in Eucla: 6:42am
assert(getLocalTime(CITY_EUCLA, 30, 9, 2157) == 642);
// UTC time: 9:47pm on 30th September, time in Eucla: 6:32am
assert(getLocalTime(CITY_EUCLA, 30, 9, 2147) == 632);
// UTC time: 9:57pm on 30th September, time in Brisbane: 7:57 am
assert(getLocalTime(CITY_BRISBANE, 30, 9, 2157) == 757);
// UTC time: 9:57pm on 1st April, time in Darwin: 7:27 am
assert(getLocalTime(CITY_DARWIN, 1, 4, 2157) == 727);
// UTC time: 9:47pm on 1st April, time in Perth: 5:47 am
assert(getLocalTime(CITY_PERTH, 1, 4, 2147) == 547);
// UTC time: 5:45am on 16th August, time in Sydney: 3:45 pm
assert(getLocalTime(CITY_SYDNEY, 16, 8, 545) == 1545);
// UTC time: 3:00 am on 27th August, time in Perth: 11:00 am
assert(getLocalTime(CITY_PERTH, 27, 8, 300) == 1100);
// UTC time: 11:00am on 24th Sep, time in Auckland: 12:00 am
// on the 25th
assert(getLocalTime(CITY_AUCKLAND, 24, 9, 1100) == 0);
// UTC time: 10:46pm on 17th April, time in Lord Howe Island:
// 9:16am on the 18th
assert(getLocalTime(CITY_LORD_HOWE_IS, 17, 4, 2246) == 916);
// UTC time: 6:00pm on 30th September, time in Broken Hill:
// 4:30am on the 1st October
assert(getLocalTime(CITY_BROKEN_HILL, 30, 9, 1800) == 430);
// UTC time: 2:00am on 25th December, time in Eucla: 10:45am
assert(getLocalTime(CITY_EUCLA, 25, 12, 200) == 1045);
// UTC time: 5:55am on 5th May, time in Sydney: 3:55pm
assert(getLocalTime(CITY_SYDNEY, 5, 5, 555) == 1555);
// UTC time: midnight on 2nd of January, time in Adelaide: 10:30pm
assert(getLocalTime(CITY_ADELAIDE, 2, 1, 0) == 1030);
// UTC time: 11am on the 1st April, time in Auckland: midnight
// on the 2nd
assert(getLocalTime(CITY_AUCKLAND, 1, 4, 1100) == 0);
// UTC time: 6:00pm on 30th July, time in Sydney: 4:00 am
assert(getLocalTime(CITY_SYDNEY, 30, 7, 1800) == 400);
// UTC time: 6:00pm on 30th July, time in Melbourne: 4:00 am
assert(getLocalTime(CITY_MELBOURNE, 30, 7, 1800) == 400);
// UTC time: 10:23am on 25th November, time in Eucla: 7:08 pm
assert(getLocalTime(CITY_EUCLA, 25, 11, 1023) == 1908);
// UTC time: 1:45pm on 15th March, time in Darwin: 11:15 pm
assert(getLocalTime(CITY_DARWIN, 15, 3, 1345) == 2315);
// UTC time: 12:15pm on 23rd June, time in Brisbane: 10:15 pm
assert(getLocalTime(CITY_BRISBANE, 23, 6, 1215) == 2215);
// UTC time: 12:35pm on 18th February, time in Sydney: 11:35 pm
assert(getLocalTime(CITY_SYDNEY, 18, 2, 1235) == 2335);
// UTC time: 10:20pm on 19th February, time in Darwin: 7:50 pm
assert(getLocalTime(CITY_DARWIN, 19, 2, 1020) == 1950);
// UTC time: 3:20pm on 28th May, time in Adelaide: 12:50 am
assert(getLocalTime(CITY_ADELAIDE, 28, 5, 1520) == 50);
// UTC time: 1:50pm on 13th August, time in Auckland: 1:50 am
assert(getLocalTime(CITY_AUCKLAND, 13, 8, 1350) == 150);
// UTC time: 2:25pm on 20th January, time in Wellington: 3:25 pm
assert(getLocalTime(CITY_WELLINGTON, 20, 1, 1425) == 325);

// ========= My own tests ===========

// UTC time: 4:30pm on 16th Feb, time in Eucla: 01:15 am
assert(getLocalTime(CITY_EUCLA, 16, 02, 1630) == 115);
// UTC time: 11:59pm on 29th Nov, time in Darwin: 09:29 am
assert(getLocalTime(CITY_DARWIN, 29, 11, 2359) == 929);
// UTC time: 11:58pm on 25th April, time in Eucla: 08:43 am
assert(getLocalTime(CITY_EUCLA, 25, 4, 2358) == 843);
// UTC time: 11:58pm on 25th April, time in Sydney: 09:58 am
assert(getLocalTime(CITY_SYDNEY, 25, 4, 2358) == 958);
// UTC time: 11:58pm on 25th April, time in Perth: 07:58 am
assert(getLocalTime(CITY_PERTH, 25, 4, 2358) == 758);
// Checks boundaries of Sydney
// UTC time: 04:00pm on 30th Sep, time in Sydney: 3:00am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1600) == 300);
// UTC time: 03:59pm on 30th Sep, time in Sydney: 1:59am
assert(getLocalTime(CITY_SYDNEY, 30, 9, 1559) == 159);
// UTC time: 02:59pm on 1st April, time in Sydney: 01:59am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1459) == 159);
// UTC time: 03:00pm on 1st April, time in Sydney: 03:00am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1500) == 200);
// UTC time: 04:00pm on 1st April, time in Sydney: 02:00am
assert(getLocalTime(CITY_SYDNEY, 1, 4, 1600) == 200);


    return EXIT_SUCCESS;
}


// Converts the time to local time
// [DO NOT CHANGE THIS PROTOTYPE!]
int getLocalTime (int city, int day, int month, int timeUTC) {

    //assign function for each city category
    int localTime = 0;
    int timeZone = 0;
    if (city >= 11) {
        timeZone = newZealandCities(day, month, timeUTC);
    } else if (city == 1 || city == 4 || city == 5 || city == 9) {
        timeZone = AUS_NODAYLIGHT(city, day, month, timeUTC);
    } else if (city == 0 || city == 2) {
        timeZone = AUS_CENTRAL(city,day,month,timeUTC);
    } else if (city == 3 || city == 6 || city == 8 || city == 10) {
        timeZone = AUS_EAST(city, day, month, timeUTC);
    } else {
        timeZone = lordH_Island(day, month, timeUTC);
    }

    //take in time zone and timeUTC to work out 24hrs time in function hour_24_format
    localTime = timeIn24HrsFormat(timeUTC, timeZone);

    return localTime;
}

int timeIn24HrsFormat(int hour, int zone) {
    int formatted, min;
    //take mins from hour and zone then add them together and mod 60 to make sure the result is not over 60
    min = (hour%100+zone%100)%60;
    //Now do the same for hour
    formatted = 100*((hour / 100 + zone / 100) % 24 + (hour % 100 + zone % 100) / 60) + min;
    return formatted%2400;
}

//function for New Zealand cities
int newZealandCities(int day, int month, int timeUTC) {

    int timeZone, localTime;
    //Daylight Saving Time Starts on 24th September so if the input month is Oct or later time is NZDT
    if (month >= 10) {
        timeZone = TIMEZONE_NZDT;
        //Daylight Saving time ends on 2nd April so if the month is March or before the time is still NZDT
    } else if (month <= 3) {
        timeZone = TIMEZONE_NZDT;
        //When the input month is April, some cases need to be considered since April is the month when time changes
    } else if (month == 4) {
        //Here NZDT is used to add with timeUTC to check if a day has passed.
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_NZDT);
        if (localTime <= timeUTC) {
            day++;
        }
        //If the day is 2 and time is 300, timezone becomes NZST
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
        //Day light saving starts on 24th Sep
    } else if (month == 9) {
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_NZST);
        //check if a day has passed
        if (localTime <= timeUTC) {
            day++;
        }
        //on the 24th if time is 200 or more, daylight saving starts
        if (day == 24) {
            //When the time is 2am daylight saving will set in otherwise the time remains in standard timezone
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
        timeZone=TIMEZONE_NZST;
    }

    return timeZone;
}

int AUS_NODAYLIGHT (int city, int day, int month, int timeUTC){
    //These cities have no daylight saving time. Assign the timezone to corresponding city
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
    //if time UTC input month is 10 or more timezone is ACDT
    if (month >= 10) {
        timeZone = TIMEZONE_ACDT;
        //if time UTC input month is 3 or less timezone is ACDT
    } else if (month <= 3) {
        timeZone = TIMEZONE_ACDT;
        //time changes on 2nd April localtime
    } else if (month==4) {
        //get localtime and check if a day has passed
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_ACDT);
        if (localTime <= timeUTC) {
            day++;
        }
        //When local day is 2 check if time is 3AM
        if (day == 2) {
            if (localTime < 300) {
                timeZone = TIMEZONE_ACDT;
            } else {
                timeZone = TIMEZONE_ACST;
            }
            //If day is 1 time is ACDT if day is more than 2 time is ACST(daylight saving ended)
        } else if (day < 2) {
            timeZone = TIMEZONE_ACDT;
        } else {
            timeZone = TIMEZONE_ACST;
        }
        //If input is 30 Sep, check localday and localtime | Here assumed time is ACST (before daylight saving starts)
    } else if (month == 9) {
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_ACST);
        if (localTime <= timeUTC) {
            day++;
        }
        //31 Sep doesnt exist but for the sake of coding think of this as 1 Oct 2017
        if (day == 31) {
            //When the time is 2am daylight saving will set in otherwise the time remains in standard timezone
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

//Same logic of function AUS_CENTRAL applies to AUS_EAST the daylight saving borders are the same the different is time offset from UTC
int AUS_EAST(int city, int day, int month, int timeUTC){

    int timeZone, localTime;
    //if time UTC input month is 10 or more timezone is AEDT
    if (month >= 10) {
        timeZone = TIMEZONE_AEDT;
        //if time UTC input month is 3 or less timezone is AEDT
    } else if (month <= 3) {
        timeZone = TIMEZONE_AEDT;
        //time changes on 2nd April localtime
    } else if (month == 4) {
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_AEDT);
        if (localTime <= timeUTC) {
            day++;
        }
        //When local day is 2 check if time is 3AM
        if (day == 2) {
            if(localTime < 300) {
                timeZone = TIMEZONE_AEDT;
            } else {
                timeZone = TIMEZONE_AEST;
            }
            //If day is 1 time is AEDT if day is more than 2 time is AEST(daylight saving ended)
        } else if (day < 2) {
            timeZone = TIMEZONE_AEDT;
        } else {
            timeZone = TIMEZONE_AEST;
        }
        //If input is 30 Sep, check localday and localtime | Here assumed time is AEST (before daylight saving starts)
    } else if (month == 9) {
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_AEST);
        if (localTime <= timeUTC) {
            day++;
        }
        //31 Sep doesnt exist but for the sake of coding think of this as 1 Oct 2017
        if (day==31) {
            //When the time is 2am daylight saving will set in otherwise the time remains in standard timezone
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

int lordH_Island(int day, int month, int timeUTC){

    int timeZone, localTime;
    //if time UTC input month is 10 or more timezone is LHDT
    if (month >= 10) {
        timeZone = TIMEZONE_LHDT;
        //if time UTC input month is 3 or less timezone is AEDT
    } else if (month <= 3) {
        timeZone=TIMEZONE_LHDT;
        //time changes on 2nd April localtime to standard time
    } else if (month == 4) {
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_LHDT);
        if (localTime <= timeUTC) {
            day++;
        }
        //When local day is 2 check if time is 2AM
        if (day == 2) {
            if (localTime < 200) {
                timeZone = TIMEZONE_LHDT;
            } else {
                timeZone=TIMEZONE_LHST;
            }
        } else if (day < 2) {
            timeZone = TIMEZONE_LHDT;
        } else {
            timeZone = TIMEZONE_LHST;
        }
        //If input is 30 Sep, check localday and localtime | Here assumed time is AEST (before daylight saving starts)
    } else if (month == 9) {
        localTime = timeIn24HrsFormat(timeUTC, TIMEZONE_LHST);
        if (localTime <= timeUTC) {
            day++;
        }
        //31 Sep doesnt exist but for the sake of coding think of this as 1 Oct 2017
        if (day == 31) {
            //When the time is 2am daylight saving will set in otherwise the time remains in standard timezone
            if (localTime < 200) {
                timeZone = TIMEZONE_LHST;
            } else {
                timeZone = TIMEZONE_LHDT;
            }
        } else {
            timeZone = TIMEZONE_LHST;
        }
    } else {
        timeZone = TIMEZONE_LHST;
    }

    return timeZone;

}




