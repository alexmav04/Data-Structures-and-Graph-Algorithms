//Convert a date in yyyy/mm/dd into "name of the month" dd, yyyy
//date:2020-09-18

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> strSplit(string, string);
bool isLeapYear(int year);
bool isValidDate(string date);
string monthConverter(int month);
string dateConverter(string date);

int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef struct dateinfo {
  int year, month, day;
} Date;

int main() {
  string dateinput;
  string msg = "";

  cin >> dateinput;
  cout << dateConverter(dateinput) << endl;

  system("pause");
  return 0;
}

//split string by a character
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

//check if the year is leap year
bool isLeapYear(int year) {
  if ((year % 4 == 0) && (year % 100 != 0))
    return true;
  else if (year % 400 == 0)
    return true;
  else
    return false;
}

//check if the type of input data is valid
bool isValidDate(string date) {
  vector<string> vstrDate = strSplit(date, "/");
  int intYear = 0, intMonth = 0, intDay = 0;

  intYear = atoi(vstrDate[0].c_str());
  intMonth = atoi(vstrDate[1].c_str());
  intDay = atoi(vstrDate[2].c_str());

  if (vstrDate.size() != 3)
    return false;

  if ((intMonth < 1) || (intMonth > 12))
    return false;

  if (isLeapYear(intYear))
    month_days[1] = 29;
  else
    month_days[1] = 28;

  if (intDay > month_days[intMonth - 1])
    return false;

  return true;
}

//convert month(a number) into its name
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

//convert input into a specified format
string dateConverter(string date) {
  string convDate = "";
  int intMonth = 0;

  if (!isValidDate(date)) {
    convDate = "It is not a valid date.";
  } else {
    intMonth = atoi(strSplit(date, "/")[1].c_str());
    convDate = monthConverter(intMonth) + " " + strSplit(date, "/")[2] + ", " +
               strSplit(date, "/")[0];
  }
  return convDate;
}
