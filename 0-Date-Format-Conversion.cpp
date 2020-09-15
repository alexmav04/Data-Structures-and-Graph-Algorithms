//Convert a date in "yyyy/mm/dd" into name of "the name of month dd, yyyy".
//author: 309652014 楊珈禎
//date: 2020-09-16

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
vector<string> strSplit(string, string);
string month_converter(int month);
bool isValidDate(vector<string> date);

int main() {
  string date, strYear, strMonth, strDay;
  vector<string> strDate;

  cout << "Enter a date (yyyy/mm/dd): " << endl;
  cin >> date;

  strDate = strSplit(date, "/");

  try {
    if (!isValidDate(strDate)) {
      throw "It is not a valid date.";
    }
    strYear = strDate[0];
    strMonth = strDate[1];
    strDay = strDate[2];

    int intMonth = atoi(strMonth.c_str());
    strMonth = month_converter(intMonth);

    cout << strMonth << " " << strDay << ", " << strYear << endl;
  }
  catch (const char *message) {
    cout << message << endl;
  }

  system("pause");
}

string month_converter(int month) {
  string txtMonth;

  switch (month) {
    case 1:
      txtMonth = "January";
      break;
    case 2:
      txtMonth = "Febuary";
      break;
    case 3:
      txtMonth = "March";
      break;
    case 4:
      txtMonth = "April";
      break;
    case 5:
      txtMonth = "May";
      break;
    case 6:
      txtMonth = "June";
      break;
    case 7:
      txtMonth = "July";
      break;
    case 8:
      txtMonth = "August";
      break;
    case 9:
      txtMonth = "September";
      break;
    case 10:
      txtMonth = "October";
      break;
    case 11:
      txtMonth = "November";
      break;
    case 12:
      txtMonth = "December";
      break;

    default:
      txtMonth = "Not a valid month.";
      break;
  }
  return txtMonth;
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

bool isValidDate(vector<string> date) {
  map<int, int> mapDays;
  mapDays[1] = 31;
  mapDays[2] = 28;
  mapDays[3] = 31;
  mapDays[4] = 30;
  mapDays[5] = 31;
  mapDays[6] = 30;
  mapDays[7] = 31;
  mapDays[8] = 31;
  mapDays[9] = 30;
  mapDays[10] = 31;
  mapDays[11] = 30;
  mapDays[12] = 31;

  bool isLeapYear = false;

  int intYear = atoi(date[0].c_str());
  int intMonth = atoi(date[1].c_str());
  int intDay = atoi(date[2].c_str());

  if (date.size() != 3)
    return false;

  if ((intMonth < 1) || (intMonth > 12))
    return false;

  if ((intYear % 4 == 0) && (intYear % 100 != 0))
    isLeapYear = true;
  else if (intYear % 400 == 0)
    isLeapYear = true;

  if (isLeapYear)
    mapDays[2] = 29;
  else
    mapDays[2] = 28;

  if (intDay > mapDays[intMonth])
    return false;

  return true;
}
