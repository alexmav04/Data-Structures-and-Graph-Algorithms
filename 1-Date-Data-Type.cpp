// Convert a date in "yyyy/mm/dd" into name of "the name of month dd, yyyy".
// author: 309652014 楊珈禎
// date:2020/09/17

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<string> strSplit(string, string);
bool isLeapYear(int year);
bool isValidDate(string date);
string monthConverter(int month);
string dateConverter(string date);
int DaysInYear(string date);
string DateSub(string date1, string date2);
string DayOfWeek(string date);

int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef struct dateinfo {
  int year, month, day;
} Date;

int main() {
  string dateinput;
  string msg = "";

  cin >> dateinput;

  if (dateinput.find("-") != dateinput.npos) {
    vector<string> date;
    date = strSplit(dateinput, "-");
    if (!isValidDate(date[0]) || !isValidDate(date[1])) {
      msg = "It is not a valid date.";
    } else {
      msg = DateSub(date[0], date[1]);
    }
  } else if (dateinput.find("+") != dateinput.npos) {

  } else if (dateinput.find("/") != dateinput.npos) {
    if (isValidDate(dateinput)) {
      msg = dateConverter(dateinput) + " is " + DayOfWeek(dateinput);
    } else {
      msg = "It is not a valid date.";
    }
  } else {
    msg = "Please enter a valid date.";
  }
  cout << msg << endl;

  system("pause");
  return 0;
}

vector<string> strSplit(string s, string sep) {
  vector<string> str_split;
  int pos_current = 0;
  int pos_next = 0;

  while (pos_next < s.length()) {
    pos_next = s.find_first_of(sep, pos_current);
    if (pos_next != pos_current) {
      string strtmp = s.substr(pos_current, pos_next - pos_current);
      if (!strtmp.empty()) {
        str_split.push_back(strtmp);
      }
    }
    pos_current = pos_next + 1;
  }
  return str_split;
}

bool isLeapYear(int year) {
  if ((year % 4 == 0) && (year % 100 != 0))
    return true;
  else if (year % 400 == 0)
    return true;
  else
    return false;
}

bool isValidDate(string date) {
  vector<string> vstrDate = strSplit(date, "/");

  int intYear = atoi(vstrDate[0].c_str());
  int intMonth = atoi(vstrDate[1].c_str());
  int intDay = atoi(vstrDate[2].c_str());

  if (vstrDate.size() != 3)
    return false;

  if ((intMonth < 1) || (intMonth > 12))
    return false;

  if (isLeapYear(intYear))
    month_days[1] = 29;
  else
    month_days[1] = 28;

  if (intDay > month_days[intMonth + 1])
    return false;

  return true;
}

string monthConverter(int month) {
  string strMonth;

  switch (month) {
  case 1:
    strMonth = "January";
    break;
  case 2:
    strMonth = "Febuary";
    break;
  case 3:
    strMonth = "March";
    break;
  case 4:
    strMonth = "April";
    break;
  case 5:
    strMonth = "May";
    break;
  case 6:
    strMonth = "June";
    break;
  case 7:
    strMonth = "July";
    break;
  case 8:
    strMonth = "August";
    break;
  case 9:
    strMonth = "September";
    break;
  case 10:
    strMonth = "October";
    break;
  case 11:
    strMonth = "November";
    break;
  case 12:
    strMonth = "December";
    break;

  default:
    strMonth = "Not a valid month.";
    break;
  }
  return strMonth;
}

string dateConverter(string date) {
  string convDate = "";

  if (!isValidDate(date)) {
    convDate = "It is not a valid date.";
  } else {
    int intMonth = atoi(strSplit(date, "/")[1].c_str());
    convDate = monthConverter(intMonth) + " " + strSplit(date, "/")[2] + ", " +
               strSplit(date, "/")[0];
  }
  return convDate;
}

int DaysInYear(string date) {
  vector<string> vstrDate = strSplit(date, "/");

  int intYear = atoi(vstrDate[0].c_str());
  int intMonth = atoi(vstrDate[1].c_str());
  int intDay = atoi(vstrDate[2].c_str());

  if (isLeapYear(intYear))
    month_days[1] = 29;
  else
    month_days[1] = 28;

  for (int i = 0; i < intMonth - 1; i++) {
    intDay += month_days[i];
  }
  return intDay;
}

string DayOfWeek(string date) {
  int subDate = atoi(DateSub("1753/01/01", date).c_str());

  string strDayofWeek = "";
  switch (subDate % 7) {
  case 6:
    strDayofWeek = "Sunday";
    break;
  case 0:
    strDayofWeek = "Monday";
    break;
  case 1:
    strDayofWeek = "Tuesday";
    break;
  case 2:
    strDayofWeek = "Wednesday";
    break;
  case 3:
    strDayofWeek = "Thursday";
    break;
  case 4:
    strDayofWeek = "Friday";
    break;
  case 5:
    strDayofWeek = "Saturday";
    break;

  default:
    break;
  }
  return strDayofWeek;
}

string DateSub(string date1, string date2) {
  string msg = "";
  vector<string> vstrDate1, vstrDate2;
  Date dtDate1, dtDate2;

  vstrDate1 = strSplit(date1, "/");
  vstrDate2 = strSplit(date2, "/");

  dtDate1.year = atoi(vstrDate1[0].c_str());
  dtDate1.month = atoi(vstrDate1[1].c_str());
  dtDate1.day = atoi(vstrDate1[2].c_str());

  dtDate2.year = atoi(vstrDate2[0].c_str());
  dtDate2.month = atoi(vstrDate2[1].c_str());
  dtDate2.day = atoi(vstrDate2[2].c_str());

  int days1, days2;
  days1 = DaysInYear(date1);
  days2 = DaysInYear(date2);

  if (!isValidDate(date1) || !isValidDate(date2)) {
    msg = "It is not a valid date.";
  } else {
    if (dtDate1.year == dtDate2.year && dtDate1.month == dtDate2.month) {
      if (dtDate1.day >= dtDate2.day) {
        msg = to_string(dtDate1.day - dtDate2.day);
      } else {
        msg = to_string(dtDate2.day - dtDate1.day);
      }
    } else if (dtDate1.year == dtDate2.year) {
      msg = to_string(days1 > days2 ? days1 - days2 : days2 - days1);
    } else {
      if (dtDate1.year > dtDate2.year) {
        swap(dtDate1.year, dtDate2.year);
        swap(dtDate1.month, dtDate2.month);
        swap(dtDate1.day, dtDate2.day);
        swap(days1, days2);
      }
      if (isLeapYear(dtDate1.year))
        days1 = 366 - days1;
      else
        days1 = 365 - days1;

      int days3 = 0;
      for (int i = dtDate1.year + 1; i < dtDate2.year; i++) {
        if (isLeapYear(i))
          days3 += 366;
        else
          days3 += 365;
      }
      msg = to_string(days1 + days2 + days3);
    }
  }

  return msg;
}

// string DateAdd(string date, int n) {}