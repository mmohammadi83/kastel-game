#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <conio.h>

using namespace std;


struct kart{
    string type;
    int point;
};

struct player{
    string name;
    int point = 0;
    vector<kart> kart_mojod;
    vector<kart> kart_nemayesh_mordegan;
};


vector<kart> karts;

int max_point;
int player_number;

void control_unit(player *);
void meghdardehi_player(vector<kart> *);
void play_game(player *);
void what_max_point();
void signin_player(player *);
void start();
void amaliat(player * , int  , bool &);
void show_kartsgame(player * , int  , bool & );
bool shart_emtiaz(player );
void shomaresh_emtiaz(player *);
bool shart_edame(player *);
void tozie_kart(player *);
int win_player_f(player *);
void show_table(player *);
void sort_players(player *);
void end_game(player *);
void show_curentkarts(vector<kart> );

void meghdardehi_kartha(){
    srand(time(0));
    kart kohnepich[30];
    kart kalekado[30];
    kart gorbegor[30];

    for(int i=0 ; i<30 ; i++){
        
        kohnepich[i].type = "kohne pich";
        kohnepich[i].point = (rand() % 15) + 1;
        kalekado[i].type = "kale kadoo";
        kalekado[i].point = (rand() % 15) + 1;
        gorbegor[i].type = "gor be gor";
        gorbegor[i].point = (rand() % 15) + 1;
    }

    for(int i=0 ; i<30 ; i++)
    {
        karts.push_back(kohnepich[i]);
        karts.push_back(kalekado[i]);
        karts.push_back(gorbegor[i]);
    }
}

int main()
{   
    system("cls");
    cout << "\n\n\n\n be bazi kastel khoshomadid.\n";
    cout << "\n\n\n\t main menu\n";
    cout << "\n 1-shoroe bazi jadid\n 2-exit\n\nentekhab: ";
    int ch;
    cin >> ch;

    switch (ch)
    {
    case 1: start();break;
    case 2: return 0; break;
    default:
        cout << "entekhab eshtebah ast.";
        getch();
        main();
    }
}

void what_max_point()
{
    cout << "hadaxar emtiaz bazi chand bashad? ";
    cin >> max_point;
}

void signin_player(player *p)
{

    for(int i=0 ; i<player_number ; i++){
        cout << "name bazikon shomare " << i+1 << " ra vared konid: ";
        cin >> p[i].name ;
    }
}

void meghdardehi_player(vector<kart> *k){
    srand(time(0));
    int count = (rand() % (karts.size()-1));
    while(k->size() < 3){
        k->push_back(karts[count]);
        karts.erase(karts.begin()+count);
    }
}

void amaliat(player *p , int i , bool &b)
{
    cout << "shomare kart mored nazar az dast khod ra entekhab konid: ";
    int choosen;
    cin >> choosen;

    cout << "shomare daste kart mored nazar barai entaghal kart entekhab shode ra entekhab konid: ";
    int row_choosen;
    cin >> row_choosen;

    cout << "shomare kart mored nazar dar dastekart entekhab shode barai entaghal kart ra entekhab konid: ";
    int kart_gharargiri;
    cin >> kart_gharargiri;

    if(!(choosen >= 1 && choosen <= 3) || !(row_choosen >= 1 && row_choosen <= player_number) || !(kart_gharargiri >= 1 && kart_gharargiri <= 6))
    {
        cout << "adad vorodi eshtebah ast.";
        getch();
        show_kartsgame(p , i , b);
    }
    else if(p[row_choosen-1].kart_nemayesh_mordegan.size() < kart_gharargiri){
        p[row_choosen-1].kart_nemayesh_mordegan.push_back(p[i].kart_mojod[choosen-1]);
        p[i].kart_mojod.erase(p[i].kart_mojod.begin() + choosen-1);
    }
    else if(p[row_choosen-1].kart_nemayesh_mordegan[kart_gharargiri-1].type == p[i].kart_mojod[choosen-1].type){
        
        bool u = 1;
        for(auto &j : p[row_choosen-1].kart_nemayesh_mordegan){
            
            if(j.type == p[i].kart_mojod[choosen-1].type && j.point == p[i].kart_mojod[choosen-1].point){
                j = p[i].kart_mojod[choosen-1];
                u = 0;
            }
        }
        if(u)
            p[row_choosen-1].kart_nemayesh_mordegan[kart_gharargiri-1] =  p[i].kart_mojod[choosen-1];
        
        p[i].kart_mojod.erase(p[i].kart_mojod.begin() + choosen-1);
    }
    
    else{
        cout << "kart ha ba ham, ham type nistand. bayad kart hai entekhab shode ham type va ham noe bashand.\n";
        getch();
        show_kartsgame(p , i , b);
    }
    
    if(p[row_choosen-1].kart_nemayesh_mordegan.size() == 6 || p[i].kart_mojod.size() == 0) b = 1;
}

void show_curentkarts(vector<kart> curentkart){
    cout << "\t\t\t  +\t\t\t";
    for(int k=0 ; k<3 ; k++){
        cout << setfill('-') << setw(16) << "  ";
    }
    cout << setfill(' ') << setw(29) <<'+' << endl;
    for(int l=0 ; l<7 ; l++){
        if(l == 2){
            cout << "\t\t\t  +\t\t\t";
            for(int k=0 ; k<curentkart.size() ; k++){
                cout << "| " << curentkart[k].type << " |  ";
            }
            
            cout << setfill(' ') << setw(29) <<'+' << endl;
        }
        else if(l == 4){
            cout << "\t\t\t  +\t\t\t";
            for(int k=0 ; k<curentkart.size() ; k++){
                cout << "| " << setfill(' ') << setw(5) << curentkart[k].point << setw(9) << " |  ";
            }
            
            cout << setfill(' ') << setw(29) <<'+' << endl;
        }
        else{
            cout << "\t\t\t  +\t\t\t";
            for(int k=0 ; k<3 ; k++){
                cout << "| " << setfill(' ') << setw(14) << " |  ";
            }
            cout << setfill(' ') << setw(29) <<'+' << endl;
        }
        
    }
    cout << "\t\t\t  +\t\t\t";
    for(int k=0 ; k<3 ; k++){
        cout << setfill('-') << setw(16) << "  ";
    }
    cout << setfill(' ') << setw(29) <<'+' << endl;

    cout << "\t\t\t  +\t\t\t";
    for(int k=1 ; k<=3 ; k++){
        cout << "  " << setfill(' ') << setw(5) << k << setw(9) << "    ";
    }
    cout << setfill(' ') << setw(29) <<'+' << endl;
}

void show_kartsgame(player *p , int i , bool &b){
    system("cls");
    
    cout << right;

    for(int j=0 ; j<player_number ; j++){
        if(j == i){
            cout << "\t\t\t  " << '+' << setfill('+') << setw(98) << '+' << endl;
            cout << "\t\t\t  " << '+' << setfill(' ') << setw(49) << p[j].name << setw(49) << '+' << endl;
            cout << "\t\t\t  " << "+ ";
            for(int k=0 ; k<6 ; k++){
                cout << setfill('-') << setw(16) << "  ";
            }
            cout << '+' << endl;

            for(int l=0 ; l<7 ; l++){
                if(l == 2){
                    cout << "\t\t\t" << j+1 << " + ";
                    for(int k=0 ; k<p[j].kart_nemayesh_mordegan.size() ; k++){
                        cout << "| " << p[j].kart_nemayesh_mordegan[k].type << " |  ";
                    }
                    for(int k=p[j].kart_nemayesh_mordegan.size() ; k<6 ; k++){
                        cout << "| " << setfill(' ') << setw(14) << " |  ";
                    }
                    cout << '+' << endl;
                }
                else if(l == 4){
                    cout << "\t\t\t  " << "+ ";
                    for(int k=0 ; k<p[j].kart_nemayesh_mordegan.size() ; k++){
                        cout << "| " << setfill(' ') << setw(5) << p[j].kart_nemayesh_mordegan[k].point << setw(9) << " |  ";
                    }
                    for(int k=p[j].kart_nemayesh_mordegan.size() ; k<6 ; k++){
                        cout << "| " << setfill(' ') << setw(14) << " |  ";
                    }
                    cout << '+' << endl;
                }
                else{
                    cout << "\t\t\t  " << "+ ";
                    for(int k=0 ; k<6 ; k++){
                        cout << "| " << setfill(' ') << setw(14) << " |  ";
                    }
                    cout << '+' << endl;
                }
            }
            cout << "\t\t\t  " << "+ ";
            for(int k=0 ; k<6 ; k++)
                cout << setfill('-') << setw(16) << "  ";
            cout << '+' << endl;

            cout << "\t\t\t  " << "+ ";
            for(int k=1 ; k<=6 ; k++){
                    cout << "  " << setfill(' ') << setw(5) << k << setw(9) << "    ";
            }
            cout << '+' << endl;
            cout << "\t\t\t  " << '+' << setfill(' ') << setw(98) << '+' << endl;
            show_curentkarts(p[i].kart_mojod);
            cout << "\t\t\t  " << '+' << setfill('+') << setw(98) << '+' << endl;
        }
        else{
            
            cout << endl;
            cout << "\t\t\t  "<< setfill(' ') << setw(50) << p[j].name << endl;
            cout << "\t\t\t  " << "  ";
            for(int k=0 ; k<6 ; k++){
                cout << setfill('-') << setw(16) << "  ";
            }
            cout << ' ' << endl;

            for(int l=0 ; l<7 ; l++){
                if(l == 2){
                    cout << "\t\t\t" << j+1 << "   ";
                    for(int k=0 ; k<p[j].kart_nemayesh_mordegan.size() ; k++){
                        cout << "| " << p[j].kart_nemayesh_mordegan[k].type << " |  ";
                    }
                    for(int k=p[j].kart_nemayesh_mordegan.size() ; k<6 ; k++){
                        cout << "| " << setfill(' ') << setw(14) << " |  ";
                    }
                    cout << ' ' << endl;
                }
                else if(l == 4){
                    cout << "\t\t\t  " << "  ";
                    for(int k=0 ; k<p[j].kart_nemayesh_mordegan.size() ; k++){
                        cout << "| " << setfill(' ') << setw(5) << p[j].kart_nemayesh_mordegan[k].point << setw(9) << " |  ";
                    }
                    for(int k=p[j].kart_nemayesh_mordegan.size() ; k<6 ; k++){
                        cout << "| " << setfill(' ') << setw(14) << " |  ";
                    }
                    cout << ' ' << endl;
                }
                else{
                    cout << "\t\t\t  " << "  ";
                    for(int k=0 ; k<6 ; k++){
                        cout << "| " << setfill(' ') << setw(14) << " |  ";
                    }
                    cout << ' ' << endl;
                }
            }
            cout << "\t\t\t  " << "  ";
            for(int k=0 ; k<6 ; k++)
                cout << setfill('-') << setw(16) << "  ";
            cout << ' ' << endl;

            cout << "\t\t\t  " << "  ";
            for(int k=1 ; k<=6 ; k++){
                    cout << "  " << setfill(' ') << setw(5) << k << setw(9) << "    ";
            }
            cout << ' ' << endl;

        }   
    }
    amaliat(p , i , b);
}

bool shart_emtiaz(player p){
    vector<string> kartha = {"kale kadoo" , "gor be gor" , "kohne pich"};
    for(auto &i : p.kart_nemayesh_mordegan){
        for(int j=0 ; j<kartha.size() ; j++){
            if(i.type == kartha[j]){
                kartha.erase(kartha.begin()+j);
            }
        }
    }
    if(kartha.size() > 0) return false;
    else return true;
}

void shomaresh_emtiaz(player *p){
    for(int i=0 ; i<player_number ; i++){
        bool sh = shart_emtiaz(p[i]);
        if(sh){
            int sum=0;
            for(auto &q : p[i].kart_nemayesh_mordegan){
                sum += q.point;
            }
            p[i].point += sum;
        }
        
    }
}

bool shart_edame(player *p){
    int max=0;
    for(int i=0 ; i<player_number ; i++){
        if(max < p[i].point){
            max = p[i].point;
        }
    }
    if(max >= max_point){
        return 0;
    }
    else return 1;
}

void tozie_kart(player *p){
    karts.clear();
    meghdardehi_kartha();
    for(int i=0 ; i<player_number ; i++){
        p[i].kart_mojod.clear();
        p[i].kart_nemayesh_mordegan.clear();
        meghdardehi_player(&(p+i)->kart_mojod);
    }
}

int win_player_f(player *p)
{
    int index;
    int max=0;
    for(int i=0 ; i<player_number ; i++){
        if(max < p[i].point){
            max = p[i].point;
            index = i;
        }
    }
    return index;
}

void sort_players(player *p){

    for(int i=0 ; i<player_number-1 ; i++){
        for(int j=i+1 ; j<player_number ; j++){
            if(p[i].point < p[j].point) swap(p[i] , p[j]);
        }
    }
}

void show_table(player *p)
{

    cout << "\n****************************************************************************************\n";

    int win_player = win_player_f(p);
    cout << endl << "\t\t\t\t    tablo emtiazat" << endl << endl;
    cout << "\t\t\t\t    " <<setfill(' ') << setw(20) << left << "name" << "   " << setw(5) << left << "point" << endl; 
    cout << "\t\t\t\t  =" << setfill('=') << setw(31) << "=" << endl;
    

    for(int i=0 ; i<player_number ; i++){
        if(i == win_player){
            cout << "\t\t\t\t*   " <<setfill(' ') << setw(20) << left << p[i].name << "   " << setw(5) << left << p[i].point << endl; 
            cout << "\t\t\t\t  =" << setfill('=') << setw(31) << "=" << endl;
        }
        else
        {    
            cout << "\t\t\t\t    " <<setfill(' ') << setw(20) << left << p[i].name << "   " << setw(5) << left << p[i].point<< endl; 
            cout << "\t\t\t\t  =" << setfill('=') << setw(31) << "=" << endl;
        }
    }
    cout << endl << "\ndar in round " << p[win_player].name << " barande shod.\n\n";
    cout << "barai edame bazi yek kelid ra bezanid ...";
}

void end_game(player *p){
    system("cls");

    sort_players(p);

    cout << "\t\t\t        " << setfill(' ') << setw(31) << ' ' << endl;
    cout << "\t\t\twinner 1-" << setfill(' ') << setw(20) << left << p[0].name << " | " << setw(3) << left << p[0].point << "  " << endl; 
    cout << "\t\t\t        " << setfill('-') << setw(31) << "-" << endl;
    for(int i=1 ; i<player_number ; i++){    
        cout << "\t\t\t       " << i+1 << "-" << setfill(' ') << setw(20) << left << p[i].name << " | " << setw(3) << left << p[i].point << "  " << endl; 
        cout << "\t\t\t        " << setfill('-') << setw(31) << "-" << endl;
    }

    cout << "\n\n\ntabriiiikkkkk!! " << p[0].name << " barande shooooddd ";
    cout <<"\n...";
}

void play_game(player *p , int i)
{
    tozie_kart(p);    
    
    bool b = 0;
    
    while (!b)
    {
        show_kartsgame(p , i , b);
        meghdardehi_player(&(p+i)->kart_mojod);
        if(i < player_number-1) i++;
        else i = 0;

    }
    shomaresh_emtiaz(p);

}

void start()
{
    system("cls");

    cout << "tedad bazikonan ra vared konid(bein 2~6): ";
    cin >> player_number;
    if(player_number > 6){
        cout << "tedad bishtar az had mojaz ast.";
        getch();
        start();
    }
    player *p = new player[player_number];
    
    signin_player(p);
    
    what_max_point();

    control_unit(p);
}

void control_unit(player *p){
    bool chek = 1;
    int i = 0;
    do{
        play_game(p , i);
        bool edame = shart_edame(p);
        if(edame){
            if(i < player_number-1) i++;
            else i = 0;
            show_table(p);
            getch();
        }
        else chek = 0;

    }while(chek);

    end_game(p);
    getch();
    main();
    
}
