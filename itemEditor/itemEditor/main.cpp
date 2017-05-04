#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    int efect;
    int valeu;
    char mor;

    cout<<"Enter a name of an item\n";
    string name;
    getline(cin,name);
    string x=name+".item";
    ofstream output;
    output.open(x.c_str());
    output<<name<<endl;

    cout<<"Enter a type of the item\n 1 - consumable\n 2 - armor\n 3 - helmet\n 4 - boots\n 5 - gloves\n 6 - ring\n";
    int type;
    cin>>type;
    output<<type<<endl;

    bool moreeffects=1;

    while(moreeffects)
    {
    cout<<"Enter an effect you want to add to the item\n 1 - HP\n 2 - defense\n 3 - attack\n 4 - persuasion\n";
    cin>>efect;
    output<<efect<<endl;

    cout<<"Enter an effect's value\n";
    cin>>valeu;
    output<<valeu<<endl;

    cout<<"Do you want to add any more effects? (Enter y/n)\n";
    cin>>mor;
    if(mor=='n')
    moreeffects=0;
    }
    return 0;
}
