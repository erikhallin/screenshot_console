#define WINVER 0x0500
#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	cout<<"Screenshot Recorder\n"<<endl;

	//ask for delay
	float delay=0;
	cout<<"How often should the screen be captured? (min) : ";
	string user_input_line;
	getline(cin,user_input_line);
	istringstream(user_input_line)>>delay;

	//set output dir
	string output_path;
	cout<<"Where should the screenshot be exported? : ";
	getline(cin,output_path);
	ofstream file_test(output_path.c_str());
	if(file_test==0)
    {
        cout<<"ERROR: Files could not be exported to the selected directory\n\n";
        return 1;
    }

    //key setup
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk=44;//printscreen key
    ip.ki.dwFlags = 0; // 0 for key press

    //loop
    clock_t t_last;
    clock_t t_now;
    t_last=clock();
    cout<<"Recording is active, close window to shutdown...\n";
    while(true)
    {
        t_now=clock();
        float time_diff=((float)t_now)/CLOCKS_PER_SEC-((float)t_last)/CLOCKS_PER_SEC;
        if(time_diff>delay*60.0)
        {
            //reset time
            t_last=t_now;

            //press key
            SendInput(1, &ip, sizeof(INPUT));
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));
        }
    }

	return 0;
}

