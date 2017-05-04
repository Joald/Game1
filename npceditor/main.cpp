#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    cout<<"Enter the name of the NPC\n";
    string name;
    getline(cin,name);
    string x=name+".npc";
    ofstream output;
    output.open(x.c_str());
    output<<name<<endl;
    cout<<"Enter the number of HP of the NPC\n";
    int hp;
    cin>>hp;
    output<<hp<<endl;
    cout<<"Enter 1 if NPC is to follow the player, 0 if not\n";
    bool follow;
    cin>>follow;
    output<<follow<<endl;
    cout<<"Enter the NPC's behaviour\n 1 - passive\n2 - aggresive\n3 - friendly\n";
    int beh;
    cin>>beh;
    output<<beh<<endl;
    return 0;
}
