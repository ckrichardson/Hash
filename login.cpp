#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.cpp"


class TestData {
  public:
    TestData();
    void setKey(const string& newKey);
    string getKey() const;
    void setPass(string password);
    string getPass() const;
    static unsigned int hash(const string& str);

  private:
    string key;
    string pass;
    static int count;
};

int TestData::count = 0;

TestData::TestData() {
}

void TestData::setKey(const string& newKey) {
    key = newKey;
}

string TestData::getKey() const {
    return key;
}

void TestData::setPass(string password)
{
  pass = password;
}

string TestData::getPass() const {
    return pass;
}

unsigned int TestData::hash(const string& str) {
    unsigned int val = 0;

    for (int i = 0; i < str.length(); ++i) {
	val += str[i];
    }

    return val;
}


int main()
{
  HashTable<TestData, string> table(8);

  string userName;
  string passWord;

      TestData temp;

  ifstream in;
  in.open("password.dat");
  in >> userName;
  while(in.good())
  {

    in >> passWord;

    temp.setKey(userName);
    temp.setPass(passWord);

    table.insert(temp);

    in >> userName;

  }

  in.close();

  table.showStructure();

  TestData newOne;
  string inputFirstName;
  string inputLastName;
  cout << "Login: " ;
  
while(cin >> inputFirstName)
{
  cout << "Password: ";
  cin >> inputLastName;

  newOne.setKey(inputFirstName);
  newOne.setPass(inputLastName);

  if(table.retrieve(newOne.getKey(), newOne))
  {
    if(newOne.getPass() == inputLastName)
    {
      cout << "Authentication successful" << endl;
    }
    else
    {
      cout << "Authentication failure" << endl;
    }
  }
  else
    cout << "Authentication failure" << endl;

  cout << "Login: ";


}





return 0;

}
