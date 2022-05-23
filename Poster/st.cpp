#include <iostream>
#include <string>

using namespace std;

class Word{
    private:
        string value;
    public:
        Word(){
            value = "";
        }

        Word(char c){
            value = "";
            value += c;
        }

        Word(string s){
            value = "";
            for(int i = 0; i<s.length(); i++){
                if(s[i] == ' ') continue;
                value += s[i];
            }
        }

        Word(const Word &w){
            value = w.value;
        }

        string Get(){
            return value;
        }

        void Info(){
            cout << "Info of the current string:\n";
            cout << "Size:" << value.length();
            cout << "\nCapacity:" << value.capacity() << endl;
        }

        Word Times(int times){
            string temp = "";
            while(times--) temp += value;
            return Word(temp);
        }

};

int main(){
    cout << "Mid Term Test 20211!\n" << endl; 

    Word w1, w2("abc123"); 

    cout<<"w1 = "<<w1.Get()<<endl; 

    cout<<"w2 = "<<w2.Get()<<endl; 

    w1.Info(); 

    w2.Info(); 

    Word w3(w2); 

    cout<<"w3 = "<<w3.Get()<<endl; 

    Word w("abc xy  123"); 

    cout<<"w = "<<w.Get()<<endl; 

    Word w4 = w2.Times(0); 

    cout<<"w4 = "<<w4.Get()<<endl; 

    Word w5 = w2.Times(3); 

    cout<<"w5 = "<<w5.Get()<<endl;

    Word w6('a'); 

    cout<<"w6 = "<<w6.Get()<<endl; 

    cout<<"\nThe End!"; 

    return 0; 
}