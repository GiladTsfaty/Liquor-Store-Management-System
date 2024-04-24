

#include "BringThemHome.h"

bool timerRunning = true;
void* displayTimePassedThread(void* arg) {
    time_t referenceTime = *(time_t*)arg;

    while (timerRunning) {
        
        time_t currentTime = time(NULL);

        
        time_t timeDiff = (time_t)difftime(currentTime, referenceTime);

        
        int days = (int)(timeDiff / (60LL * 60 * 24));
        int hours = (int)((timeDiff % (60LL * 60 * 24)) / (60LL * 60));
        int minutes = (int)((timeDiff % (60LL * 60)) / 60);
        int seconds = (int)(timeDiff % 60);

        
        printf("Time passed since October 7, 2023: %d days, %02d hours, %02d minutes, %02d seconds\n", days, hours, minutes, seconds);
        fflush(stdout);

       
        Sleep(1000);
    }

    return NULL;
}

void BringThemHomeNow(Inventory* inventory) {
    
    const char* names[NUM_NAMES] = {
            "AVIV ATZILI", "Or Avinatan", "EVYATAR DAVID", "AVERA MANGISTO", "AVRAHAM MONDER","AGAM BERGER", "OHAD BEN AMI", "OHAD YAHALOMI", "OR LEVI", "HADAR GOLDIN",
            "ORON SHAUL", "ORI DANINO", "URIEL BARUCH", "ILAN VAYS", "ITZIK ELGARAT","ITZIK GELERENTER", "ITAY CHEN", "ITAY SVIRSKY", "EITAN HORN ", "EITAN LEVI",
            "EITAN MOR", "ALON OHEL", " ELI SHARABI", "ELIYA CHOHEN", "ELIYAHU MARGALIT", "ELYAKIM LIBERMAN", "ALEX LUBANOV", "ALEX DANZIG", "ALMOG MEIR JAN", "ALMOG SARUSI",
            "ELAD KAZIR", "ELKANA BOHBOT", "EMILY TEHILA DAMARI", "ANDREY KOZLOV", "ASSAF HAMAMMI", "ARBEL YEHUD", "ARIEL BIBAS", "ARIEL CUNIO", "ARIE ZALMANOVICH", "BENAWATH SITAO",
            "Bar Kuperstein", "Gadi Haggai", "Gadi Moshe Mozes", " Judith Weinstein Haggai", "Joshua Loitu Mollel", "JOSHI BIPIN", "GUY EILUZ", "GUY GILBOA DALLAL", "GALI BERMAN", "DAVID CUNIO",
            "Dolev Yehud", "Doron Stainbreher", "DANIRL PERETZ","Daniela gilboa", "DROR OR" ,"HIRSH GOLDBERG POLIN", "Hisham al-Sayed" , "Sriaoun Watchara", "Ziv Berman" , "HAIM PERI",
            "Hamza Al Zaydana", "Hanan Yablonka" , "TAL HAYIMI", "TAL SHOHAM", "Yair Horn", "YAIR YAAKOV", "", "Yegev Buchshtav", "Yonatan Samarno", "YOSSI SHARABI",
            "Yossef Al Zaydana", "Yossef Haim Ohana", "Yoram Metzger","Yarden Bibas", "Kfir Bibas" ,"Camel Gat", "Lior Rodaif" , "Liri Albag", "Mohammad Alatrash" , "MISHEL NISBAUM",
            "Meni Godard", "MASKIM HERKIN" , "Angrest Matan", "Matan Tzangauker", "Nadav Popplewell", "Pinta Netafong", "Nimrod Cohen", "NOA ARGAMANI", "NAAMA LEVI", "SAHAR BARUCH",
            "Sudthisak Rinthalak", " Suntaya Akrasi", "SORSAK ROMANO","Stian Swanakam", "Alexander Trufanov" ,"EDEN YERUSHLAMI", "ODED LIFSITZ" , "OZ DANIEL", "Omer Wenkert" , "Omer Neutra",
            "OMER KALDERON ", "OMER SHEM TOV" , " OMRI MIRAN", "OFFER KALDERON", "IDAN ALEXANDER", "Idan Shtivi", "AMIRAM KUPER", "AMIT ESTER BUSKILA", "INBER  HAIMAN", "OFRA  KEYDAR",
            "Farhan Al-Qadi ", "Pongsak Tanna", "ZAHI IDAN","KIRIL BRODSKI", "Keith Samuel Sigal" ,"Karina Ariev", "RAVID KATZ" , "Rom Braslavski", "ROMI GONEN" , "RON BENYAMIN",
            "RONEN ENGEL", "RON GVILI" , "SEGEV KALFON", "SAGI DEKEL CHEN", "SHAI LEVINSON", "SHIRI BIBAS", "SHLOMI ZIV", "SHLOMO MANSUR", "SHANI LUK", "TOMER AHIMAS",
            "TAMIR ADAR","TAMIR NIMRODI"
    };

    srand((int)time(NULL)); 

    
    int nameIndex = rand() % NUM_NAMES;
    const char* selectedName = names[nameIndex];

    
    if (inventory->whiskeysCount > 0) {
        int whiskeyIndex = rand() % inventory->whiskeysCount;
        Whiskey* selectedWhiskey = &inventory->whiskeyArray[whiskeyIndex];

        
        printf("WE DONT HAVE TIME!\n");
        printf("WE DONT HAVE TIME!\n");

        printf("ONE name = the entire world\n");
        printf("Bring ->>>    %s    <<<---   home now!\n", selectedName);

        printf("Sending a bottle of %s whiskey to their family.\n", selectedWhiskey->brand);

       
        if (selectedWhiskey->amountAvailable > 0) {
            selectedWhiskey->amountAvailable--;
        }
    }
    else {
        printf("No whiskey bottles available in the inventory.\n");
    }

    
    struct tm referenceDate = { 0 };
    referenceDate.tm_year = 2023 - 1900;   
    referenceDate.tm_mon = 9;              
    referenceDate.tm_mday = 7;             
    time_t referenceTime = mktime(&referenceDate);

    
    HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)displayTimePassedThread, &referenceTime, 0, NULL);
    if (thread == NULL)
    {
     
        printf("Failed to create the timer thread.\n");
        return;
    }

    
    printf("Press Enter to return to the menu...\n");
    getchar();

    
    timerRunning = false;

    
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);

    
    system("cls");
}