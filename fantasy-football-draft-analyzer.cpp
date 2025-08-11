#include <iostream>
#include <cstring>

using namespace std;

/* struct used to store different player info
    will be used as an array to store different values for each player in array
    value = how many points the player is worth; used for draft grade
    position = stores integer based on position the player plays
    age = stores the age in years of how old the player is*/
struct player_info
{
    int value;
    int position;
    int age;
};

/* struct used to store overall data for the team
   value_sum = total of all values assigned with each player
   position_0_sum = counter for # of QB drafted
   position_1_sum = counter for # of WR drafted
   position_2_sum = counter for # of RB drafted
   position_3_sum = counter for # of TE drafted
   position_4_sum = counter for # of K drafted
   position_5_sum = counter for # of DEF drafted
   age_avg = average age of player on the user's team
   draft_grade = grade/letter of user's team based on value_sum*/
struct team_info
{
    int value_sum;
    int position_0_sum;
    int position_1_sum;
    int position_2_sum;
    int position_3_sum;
    int position_4_sum;
    int position_5_sum;
    double age_avg;
    char draft_grade;
};

// outputs greeting, purpose of program, and rules for program
void intro(void);


/// <summary> prompts user to enter and store respones in array; NAMES ONLY
/// <param name="roster"></param> points to array with all user entered names
/// <param name="team_size"></param> size of user's team
void get_user_roster(string* roster, int team_size);


/// <summary> compares the names entered by the user to array with all fantasy relavent names and stores values
/// <param name="nfl_names"></param> points to array with list of strings of all fantasy relavent names
/// <param name="user_roster"></param> points to array with list of strings of user entered names
/// <param name="team_size"></param> size of user's team
/// <param name="user_team"></param> stores values associated with user's player (age, value, position)
void store_player_info(string* nfl_names, string* user_roster, int team_size, player_info* user_team);

/// <summary> uses switch case to count how many of each position the user drafted
/// <param name="user_player_data"></param> points to array with all the players' info
/// <param name="user_team_data"></param> points to array that has general info about team; the counters for each position are stored here
/// <param name="team_size"></param> size of user's team
void calc_position_sum(player_info* user_player_data, team_info* user_team_data, int team_size);

/// <summary> calculates the average age of players on the team
/// <param name="user_player_data"></param> points to array with all the players' info including their age
/// <param name="user_team_data"></param> points to array that will store the sum of the age, then will calculate and store average age
/// <param name="team_size"></param> size of user's team
void calc_age_avg(player_info* user_player_data, team_info* user_team_data, int team_size);

/// <summary> sums the value of team and assigns draft grade
/// <param name="user_player_data"></param> points to array that has every player value of the user's team
/// <param name="user_team_data"></param>  points to array that will store the sum of the player values
/// <param name="team_size"></param> size of user's team
void calc_draft_grade(player_info* user_player_data, team_info* user_team_data, int team_size);

// displays results (draft grade, # of each position, average age, total value)
void print_results(team_info* user_team_data);

// large array that contains names of every fantasy relavent player for the program
string nfl_names[250] = { "JaMarrChase" ,"SaquonBarkley" , "JustinJefferson", "BijanRobinson",
    "CeeDeeLamb", "PukaNacua", "AmonRaStBrown", "JahmyrGibbs", "NicoCollins", "MalikNabers", "DrakeLondon", "BrianThomas",
    "AJBrown", "DerrickHenry", "DeVonAchane", "BrockBowers", "TyreekHill", "JaxonSmithNjigba", "TreyMcBride", "LaddMcConkey", "TeeHiggins",
    "JoshAllen", "BuckyIrving", "LamarJackson", "GarrettWilson", "JoshJacobs", "TerryMcLaurin", "ChristianMcCaffrey", "JonathanTaylor", "MikeEvans",
    "JaydenDaniels", "BreeceHall", "ChaseBrown", "DavanteAdams", "MarvinHarrisonJr", "DJMoore", "AshtonJeanty", "KyrenWilliams", "TJHockenson", "JalenHurts",
    "JamesCook", "KennethWalker", "ZayFlowers", "RasheeRice", "CourtlandSutton", "ChrisOlave", "AlvinKamara", "JoeBurrow", "DKMetcalf", "ChubaHubbard", "JaylenWaddle",
    "JoeMixon", "GeorgeKittle", "JamesConner", "DeVontaSmith", "ChrisGodwin", "JordanAddison", "JamesonWilliams", "GeorgePickens", "DavidMontgomery",
    "BakerMayfield", "OmarionHampton", "PatrickMahomes", "JerryJeudy", "XavierWorthy", "SamLaPorta", "IsiahPacheco", "TyroneTracy", "NajeeHarris", "AaronJones",
    "TonyPollard", "BrandonAiyuk", "RomeOdunze", "KhalilShakir", "JaredGoff", "JaylenWarren", "JonnuSmith", "MarkAndrews", "KylerMurray", "JustinHerbert",
    "JakobiMeyers", "BrianRobinson", "CalvinRidley", "DAndreSwift", "TravisKelce", "DeeboSamuel", "DavidNjoku", "EvanEngram", "TravisEtienne",
    "JordanLove", "RhamondreStevenson", "JaydenReed", "BoNix", "CooperKupp", "BrockPurdy", "JoshDowns", "MichaelPittmanJr", "CalebWilliams",
    "RicoDowdle", "StefonDiggs", "TyjaeSpears", "JalenMcMillan", "DaltonKincaid", "JakeFerguson", "JavonteWilliams", "RachaadWhite", "TuckerKraft",
    "CJStroud", "JKDobbins", "DarnellMooney", "KeenanAllen", "RickyPearsall", "DakPrescott", "TuaTagovailoa", "ZachCharbonnet", "TankBigsby", "ChristianKirk",
    "DrakeMaye", "TreVeyonHenderson", "AmariCooper", "TrevorLawrence", "MatthewStafford", "AnthonyRichardson", "KeonColeman", "DallasGoedert", "JeromeFord",
    "BlakeCorum", "HollywoodBrown", "AustinEkeler", "HunterHenry", "TetairoaMcMillan", "QuinshonJudkins", "RashidShaheed", "QuentinJohnston",
    "DeAndreHopkins", "TylerAllgeier", "RomeoDoubs", "KylePitts", "RayDavis", "GenoSmith", "AdamThielen", "SamDarnold", "BraelonAllen",
    "JaylenWright", "BryceYoung", "MarvinMims", "PatFreiermuth", "JaleelMcLaughlin", "JustinFields", "RashodBateman", "IsaacGuerendo",
    "XavierLegette", "ZachErtz", "AdonaiMitchell", "DylanSampson", "TreyBenson", "ColeKmet", "TylerWarren", "NickChubb",
    "CadeOtton", "MarShawnLloyd", "WanDaleRobinson", "DeMarioDouglas", "JJMcCarthy", "MichaelWilson", "LutherBurden",
    "EmekaEgbuka", "RoschonJohnson", "AudricEstime", "MatthewGolden", "IsaiahLikely", "BhayshulTuten",
    "DaltonSchultz", "DontayovionWicks", "DiontaeJohnson", "KalebJohnson", "CameronWard", "AntonioGibson", "CamSkattebo", "JoshuaPalmer",
    "JaTavionSanders", "KimaniVidal", "MikeGeisicki", "BrandinCooks", "KendreMiller", "TreHarris", "ShedeurSanders",
    "IsaiahBond", "ColstonLoveland", "DevinSingletary", "TravisHunter", "NoahFant", "DerekCarr",
    "GabeDavis", "DevinNeal", "DamienMartinez", "JalenTolbert", "OllieGordon", "ChristianWatson", "JusticeHill", // kickers start here
    "BrandonAubrey", "CameronDicker", "JustinTucker", "KaimiFairbairn", "JasonSanders", "EvanMcPherson",
    "HarrisonButker", "TylerBass", "JakeElliott", "YounghoeKoo", "JasonMyers", "JakeMoody", "DanielCarlson", "AlexKessman", "AlexHale",
    "Arizona", "Atlanta", "Baltimore", "Buffalo", "Carolina", "Chicago", "Cincinnati", "Cleveland", "Dallas", "Denver", "Detroit", "GreenBay", // defenses start here
    "Houston", "Indianapolis", "Jacksonville", "KansasCity", "LasVegas", "LosAngelesChargers", "LosAngelesRams",
    "Miami", "Minnesota", "NewEngland", "NewOrleans", "NewYorkGiants", "NewYorkJets", "Philadelphia", "Pittsburgh",
    "SanFrancisco", "Seattle", "TampaBay", "Tennessee", "Washington" };

// large array that contains position of every fantasy relavent player for the program
const int nfl_positions[250] = { 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 3, 1, 1, 3, 1, 1, 0, 2, 0, 1, 2, 1, 2, 2,
1, 0, 2, 2, 1, 1, 1, 2, 2, 3, 0, 2, 2, 1, 1, 1, 1, 2, 0, 1, 2, 1, 2, 3, 2, 1, 1, 1, 1, 1, 2, 0, 2, 0, 1, 1, 3, 2, 2, 2, 2, 2, 1, 1, 1, 0,
2, 3, 3, 0, 0, 1, 2, 1, 2, 3, 1, 3, 3, 2, 0, 2, 1, 0, 1, 0, 1, 1, 0, 2, 1, 2, 1, 3, 3, 2, 2, 3, 0, 2, 1, 1, 1, 0, 0, 2, 2, 1, 0, 2, 1, 0,
0, 0, 1, 3, 2, 2, 1, 2, 3, 1, 2, 1, 1, 1, 2, 1, 3, 2, 0, 1, 0, 2, 2, 0, 1, 3, 2, 0, 1, 2, 1, 3, 1, 2, 2, 3, 3, 2, 3, 2, 1, 1, 0, 1, 1, 1,
2, 2, 1, 3, 2, 3, 1, 1, 2, 0, 2, 2, 1, 3, 2, 3, 1, 2, 1, 0, 1, 3, 2, 1, 3, 0, 1, 2, 2, 1, 2, 1, 2,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, // kickers
5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }; // defenses

// large array that contains age of every fantasy relavent player for the program
const int nfl_age[250] = { 25, 28, 25, 23 ,26 ,23 ,25, 23, 26, 21, 23, 22, 27, 31, 23, 22, 31, 23, 25, 23, 26, 28, 22, 28, 24, 27, 29, 28, 26, 31, 24, 23, 25, 32, 22,
28, 21, 24, 27, 26, 25, 24, 24, 25, 29, 24, 29, 28, 27, 25, 26, 28, 31, 29, 26, 29, 23, 24, 24, 27, 30, 22, 29, 26, 22, 24, 26, 25, 27, 30, 28, 27, 22, 25, 30, 26, 29, 29, 27,
27, 28, 26, 30, 26, 35, 29, 28, 30, 26, 26, 27, 25, 25, 31, 25, 23, 27, 23, 26, 31, 23, 23, 25, 26, 25, 26, 24, 23, 26, 27, 32, 24, 31, 27, 24, 22, 28, 22, 22, 30, 25, 37, 22,
21, 30, 25, 24, 27, 29, 30, 22, 21, 26, 23, 32, 25, 25, 24, 25, 34, 34, 27, 21, 22, 23, 23, 26, 24, 26, 25, 24, 24, 34, 22, 20, 22, 26, 22, 29, 26, 24, 24, 24, 22, 25, 21, 22,
24, 21, 21, 25, 23, 28, 23, 28, 21, 22, 26, 23, 25, 22, 23, 29, 31, 22, 23, 23, 21, 21, 27, 21, 27, 34, 26, 21, 21, 26, 21, 25, 27,
30, 24, 35, 31, 29, 25, 29, 28, 30, 30, 33, 25, 30, 24, 26, // kickers
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // defenses -- no age associated with defense / special teams

// large array that contains value of every fantasy relavent player for the program
const int nfl_value[250] = { 10000, 9950, 9750, 9800, 9700, 9600, 9600, 9650, 9500, 9560, 9380, 9470, 9350, 9200, 9300, 9200,
8900, 8950, 8900, 9150, 9000, 8700, 8500, 8500, 8400, 8750, 8600, 9100, 8700, 8300, 8300, 8200, 8450, 8200, 8400, 7400, 9230, 8380,
6600, 8000, 8100, 7250, 7400, 7900, 7400, 6800, 7100, 9300, 7300, 8500, 6700, 7500, 7100, 6700, 7100, 6900, 6950, 7200, 6600, 6600,
5800, 7900, 5850, 6400, 7800, 6500, 5400, 5100, 4950, 5700, 6100, 6350, 6000, 5900, 4600, 6000, 5000, 5000, 5500, 4300, 5900, 5200,
6800, 5800, 5000, 6500, 3850, 4500, 4650, 4200, 3800, 6000, 5050, 5600, 4200, 5800, 4750, 5550, 2200, 5900, 3300, 3500, 3300, 3250,
4250, 4150, 4450, 4000, 2000, 5150, 2400, 6000, 3900, 2800, 4800, 3000, 4100, 4200, 7000, 2600, 3900, 2800, 2950, 4450, 2820, 1900,
2750, 3800, 2400, 2200, 7600, 6500, 3900, 2900, 1950, 2750, 2700, 1950, 2900, 2850, 1850, 1900, 1800, 1750, 1750, 3800, 1750, 1700,
5200, 1700, 3000, 2810, 2300, 1300, 2500, 3250, 1600, 5800, 1650, 1650, 1500, 1400, 1300, 3400, 1300, 5300, 5400, 1200, 1200, 6400,
2800, 4650, 1200, 1100, 1100, 6450, 2600, 1050, 5000, 1050, 1000, 1000, 1000, 950, 900, 4850, 900, 0, 4900, 850, 7600, 850, 800, 800,
750, 750, 750, 750, 700, 750,
700, 700, 650, 650, 650, 600, 600, 550, 550, 500, 450, 400, 400, 350, 400, // kickers
300, 250, 400, 300, 200, 300, 250, 200, 300, 450, 400, 350, 350, 300, 200, 350, 250, 350, 350, 250, 400, 250, 200, 200, 200, 400, 400, // defenses
300, 300, 300, 100, 300 };

int main()
{
    // size of team
    const int team_size = 15;
    // stores names entered by user
    string user_roster[team_size];
    // stores player data based on the names found
    player_info user_player_data[team_size];
    // stores data about the team by using values from the player data
    team_info user_team_data;

    // initialize variables
    for (int i = 0; i < team_size; i++)
    {
        user_player_data[i].age = 0;
        user_player_data[i].position = 0;
        user_player_data[i].value = 0;
    }
    user_team_data.value_sum = 0;
    user_team_data.position_0_sum = 0;
    user_team_data.position_1_sum = 0;
    user_team_data.position_2_sum = 0;
    user_team_data.position_3_sum = 0;
    user_team_data.position_4_sum = 0;
    user_team_data.position_5_sum = 0;
    user_team_data.age_avg = 0;
    user_team_data.draft_grade = 'z';

    /*
    1. display purpose of program
    2. ask and store user's roster
    3. find names the user entered and store relavent values in player data
    4. count the number of each position drafted and store in team data
    5. sum and average the age of drafted players by using player data and storing in team data
    6. sum team value and assign a draft grade
    7. output results to user
    8. end program
    */

    intro();
    get_user_roster(user_roster, team_size); 
    store_player_info(nfl_names, user_roster, team_size, user_player_data); 
    calc_position_sum(user_player_data, &user_team_data, team_size);
    calc_age_avg(user_player_data, &user_team_data, team_size);
    calc_draft_grade(user_player_data, &user_team_data, team_size);
    print_results(&user_team_data);
    return 0;
}

// display purpose and rules for program
void intro(void)
{
    cout << "============================================================================================" << endl << endl;
    cout << "\t\t\t\tWelcome to the Fantasy Football Draft Analyzer!" << endl;
    cout << "The purpose of this program is to assign a draft grade to your fantasy football team and provide other data." << endl;
    cout << "There are weight values associated with the players in the draft. They are largely based on ADP from sleeper.com" << endl;
    cout << "This program assumes that you are playing in a 12 person league with 1.0 PPR scoring." << endl;
    cout << "Additionally, teams must meet the following requirements: " << endl;
    cout << "\t-1 QB" << endl;
    cout << "\t-2 WR" << endl;
    cout << "\t-2 RB" << endl;
    cout << "\t-1 TE" << endl;
    cout << "\t-2 FLX" << endl;
    cout << "\t-1 K" << endl;
    cout << "\t-1 DEF" << endl;
    cout << "\t-5 BENCH" << endl;
    cout << "\t= 15 rounds" << endl;
    cout << "You will be prompted to enter the names of your players one by one, then the program will output your results." << endl;
    cout << "The naming convention must follow these rules: " << endl;
    cout << "\t1) No spaces, hyphens, or apostrophes in names" << endl;
    cout << "\t2) Proper capitalization must be used (first and last)";
    cout << "\t3) Use nicknames or Jr if that is their name on fantasy football websites" << endl;
    cout << "\tEx: Puka Nacua -> PukaNacua" << endl;
    cout << "\tEx: Amon-Ra St. Brown -> AmonRaStBrown" << endl;
    cout << "\tEx: Marquise Irving / Bucky Irving -> BuckyIrving" << endl << endl;
    cout << "============================================================================================" << endl << endl;
}

// prompts and stores the names of the players the user drafted
void get_user_roster(string* roster, int team_size)
{
    /*user's roster is stored in an array
    initialized using loop
    */
    for (int i = 0; i < team_size; i++)
    {
        if (i == 0) // 1st pick
        {
            cout << i + 1 << "st pick: ";
            cin >> roster[i];
        }
        if (i == 1) // 2nd pick
        {
            cout << i + 1 << "nd pick: ";
            cin >> roster[i];
        }
        if (i == 2) // 3rd pick
        {
            cout << i + 1 << "rd pick: ";
            cin >> roster[i];
        }
        if (i >= 3) // picks 4-15
        {
            cout << i + 1 << "th pick: ";
            cin >> roster[i];
        }
    }
}

// compare name of entered string to array with all of the names and store associated values
void store_player_info(string* nfl_names, string* user_roster, int team_size, player_info* user_team)
{
    for (int i = 0; i < team_size; i++) // 0-14 for the number of players drafted
    {
        for (int j = 0; j < 250; j++) // loop searches through big array for a match
        {
            if (user_roster[i] == nfl_names[j]) // if the name entered matches with the larger array
            {
                user_team[i].age = nfl_age[j]; // store the player's age
                user_team[i].position = nfl_positions[j]; //store the player's position
                user_team[i].value = nfl_value[j]; // store the player's value

                break;
            }
        }
    }
}

// count the number of each position 
void calc_position_sum(player_info* user_player_data, team_info* user_team_data, int team_size)
{
    /* go through each player and depending on position, add 1 to counter
    0 - QB
    1- WR
    2 - RB
    3 - TE
    4 - K
    5 - DEF
    */
    for (int i = 0; i < team_size; i++)
    {

        switch (user_player_data[i].position)
        {
        case 0:
            user_team_data->position_0_sum += 1;
            break;
        case 1:
            user_team_data->position_1_sum += 1;
            break;
        case 2:
            user_team_data->position_2_sum += 1;
            break;
        case 3:
            user_team_data->position_3_sum += 1;
            break;
        case 4:
            user_team_data->position_4_sum += 1;
            break;
        case 5:
            user_team_data->position_5_sum += 1;
            break;
        }
    }
}

// sum and average the age of the players and store this in team_data
void calc_age_avg(player_info* user_player_data, team_info* user_team_data, int team_size)
{

    for (int i = 0; i < team_size; i++)
    {
        user_team_data->age_avg += user_player_data[i].age;
    }
    user_team_data->age_avg /= (team_size - (user_team_data->position_5_sum)); // has to subtract # of defense because no age associated w/ them
}

/* sum values and assign draft grade
0 = F
1-70000 = D
70001-80000 = C
80001-85000 = B
85001-200000 = A

If z is returned, then there is a problem
*/
void calc_draft_grade(player_info* user_player_data, team_info* user_team_data, int team_size)
{

    for (int i = 0; i < team_size; i++)
    {
        user_team_data->value_sum += user_player_data[i].value;
    }

    if (user_team_data->value_sum == 0)
    {
        user_team_data->draft_grade = 'F';
    }
    if (user_team_data->value_sum > 0 && user_team_data->value_sum <= 70000)
    {
        user_team_data->draft_grade = 'D';
    }
    if (user_team_data->value_sum > 70000 && user_team_data->value_sum <= 80000)
    {
        user_team_data->draft_grade = 'C';
    }
    if (user_team_data->value_sum > 80000 && user_team_data->value_sum <= 85000)
    {
        user_team_data->draft_grade = 'B';
    }
    if (user_team_data->value_sum > 85000 && user_team_data->value_sum <= 200000)
    {
        user_team_data->draft_grade = 'A';
    }
}

// output results to user
void print_results(team_info* user_team_data)
{
    cout << endl << endl << "=================================================================" << endl;
    cout << "\t\t\tDraft Grade: " << user_team_data->draft_grade << endl;
    cout << "\tAverage age of team: " << user_team_data->age_avg << " years old" << endl;
    cout << "\tValue sum: " << user_team_data->value_sum << endl;
    cout << "# of QB: " << user_team_data->position_0_sum << endl;
    cout << "# of WR: " << user_team_data->position_1_sum << endl;
    cout << "# of RB: " << user_team_data->position_2_sum << endl;
    cout << "# of TE: " << user_team_data->position_3_sum << endl;
    cout << "# of K: " << user_team_data->position_4_sum << endl;
    cout << "# of DST: " << user_team_data->position_5_sum << endl;
    cout << endl << "=================================================================" << endl;
}
