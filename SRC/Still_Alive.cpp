#include "Dependencies.h"
#include "Art.h"

int main()
{
////////////////////////////////////////Init - Linux////////////////////////////////////////
#ifdef linux
    colour(9); //light grey text
    colour(10); //black background
    ctrlC_catcher();
    system("clear");
    cursor(false);

    checkScreenSize();
    checkFileExists("portal_sa.wav");

    gotoxy(0, getxy(false, true) - 5); centerText(getxy(true, true), "Portal 1 ending credits");
    gotoxy(0, getxy(false, true) - 3); centerText(getxy(true, true), "made by Ink Phoenix");
    gotoxy(0, getxy(false, true) + 2); centerText(getxy(true, true), "press Enter to continue");
    std::cin.get();

    colourScreen();
#endif


////////////////////////////////////////Init - Windows////////////////////////////////////////
#ifdef _WIN32
    colour(9); //light grey text
    colour(10); //black background
    system("CLS");
    cursor(false);
    windowResize_XY(950, 650);

    checkScreenSize();
    checkFileExists("portal_sa.wav");

    centerText_XY(getxy(true, true), getxy(false, true) - 5, "Portal 1 ending credits");
    centerText_XY(getxy(true, true), getxy(false, true) - 3, "made by Ink Phoenix");
    centerText_XY(getxy(true, true), getxy(false, true) + 2, "press Enter to continue");
    cursor(false);
    std::cin.get();

    colourScreen();
#endif


////////////////////////////////////////XCode (Animation)////////////////////////////////////////

    gotoxy(0, 0);
    emptyBoard();

    gotoxy(3, 1); log(75, 0, false, "Fo");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(5, 1); log(0, 75, false, "_");

    gotoxy(5, 1); log(0, 75, false, "r_");
    gotoxy(6, 1); log(0, 75, false, "m_");
    gotoxy(7, 1); log(0, 75, false, "s_");
    gotoxy(8, 1); log(0, 75, false, " _");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(9, 1); log(0, 75, false, " ");

    gotoxy(9, 1); log(75, 0, false, "FORM");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(13, 1); log(0, 75, false, "_");

    gotoxy(13, 1); log(0, 75, false, "-_");
    gotoxy(14, 1); log(0, 75, false, "2_");
    gotoxy(15, 1); log(0, 75, false, "9_");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(16, 1); log(0, 75, false, " ");

    gotoxy(16, 1); log(75, 0, false, "8272");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(20, 1); log(0, 75, false, "_");

    gotoxy(20, 1); log(0, 75, false, "8_");
    gotoxy(21, 1); log(0, 75, false, "1_");
    gotoxy(22, 1); log(0, 75, false, "-_");

    gotoxy(23, 1); log(0, 0, false, "1");
    gotoxy(58, 15); log(0, 75, false, "_");

    gotoxy(24, 1); log(75, 0, false, "2:");
    gotoxy(3, 2); log(75, 0, false, "T");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(4, 2); log(0, 75, false, "_");

    gotoxy(4, 2); log(0, 75, false, "e_");
    gotoxy(5, 2); log(0, 75, false, "s_");
    gotoxy(6, 2); log(0, 75, false, "t_");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(7, 2); log(0, 75, false, " ");

    gotoxy(8, 2); log(75, 0, false, "Ass");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(11, 2); log(0, 75, false, "_");

    gotoxy(11, 2); log(0, 75, false, "e_");
    gotoxy(12, 2); log(0, 75, false, "s_");
    gotoxy(13, 2); log(0, 75, false, "s_");
    gotoxy(14, 2); log(0, 75, false, "m_");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(15, 2); log(0, 75, false, " ");

    gotoxy(15, 2); log(75, 0, false, "ent");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(18, 2); log(0, 75, false, "_");

    gotoxy(18, 2); log(0, 75, false, " _");
    gotoxy(19, 2); log(0, 75, false, "R_");
    gotoxy(20, 2); log(0, 75, false, "e_");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(21, 2); log(0, 75, false, " ");

    gotoxy(21, 2); log(75, 0, false, "port");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(3, 3); log(0, 75, false, "_");
    gotoxy(3, 5); log(0, 75, false, "_");
    gotoxy(3, 3); log(0, 315, false, " ");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(3, 5); log(0, 315, false, " ");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(3, 5); log(0, 315, false, "_");
    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(3, 5); log(0, 315, false, " ");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(3, 5); log(0, 315, false, "_");
    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(3, 5); log(0, 315, false, " ");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(3, 5); log(0, 315, false, "_");
    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(3, 5); log(0, 315, false, " ");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(3, 5); log(0, 315, false, "_");
    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(3, 5); log(0, 315, false, " ");

#ifdef linux
    routeALSAErrors();
    musicPlay("portal_sa.wav");
#endif

#ifdef _WIN32
    musicPlay("portal_sa.wav");
#endif

    gotoxy(3, 5); log(0, 75, false, "T");
    gotoxy(58, 15); log(0, 0, false, " ");

    gotoxy(4, 5); log(0, 75, false, "h_");
    gotoxy(5, 5); log(0, 75, false, "i_");
    gotoxy(6, 5); log(0, 75, false, "s_");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(7, 5); log(0, 75, false, " ");

    gotoxy(8, 5); log(75, 0, false, "wa");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(10, 5); log(0, 75, false, "_");

    gotoxy(10, 5); log(0, 75, false, "s_");
    gotoxy(11, 5); log(0, 75, false, " _");
    gotoxy(12, 5); log(0, 75, false, "a_");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(13, 5); log(0, 75, false, " ");

    gotoxy(14, 5); log(75, 0, false, "tr");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(16, 5); log(0, 75, false, "_");

    gotoxy(16, 5); log(0, 75, false, "i_");
    gotoxy(17, 5); log(0, 75, false, "u_");
    gotoxy(18, 5); log(0, 75, false, "m_");

    gotoxy(58, 15); log(0, 0, false, "_");
    gotoxy(19, 5); log(0, 75, false, " ");

    gotoxy(19, 5); log(75, 0, false, "ph.");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(3, 6); log(0, 60, false, "_");

    gotoxy(58, 15); log(60, 0, false, ">LI");

    gotoxy(61, 15); log(0, 0, false, "_");
    gotoxy(3, 6); log(0, 60, false, " ");

    gotoxy(61, 15); log(0, 60, false, "S_");
    gotoxy(62, 15); log(0, 60, false, "T_");
    gotoxy(63, 15); log(0, 60, false, " _");
    gotoxy(64, 15); log(0, 60, false, "P_");
    gotoxy(65, 15); log(0, 60, false, "E_");

    gotoxy(66, 15); log(0, 0, false, " ");
    gotoxy(3, 6); log(0, 60, false, "_");

    gotoxy(66, 15); log(60, 0, false, "RSON");

    gotoxy(3, 6); log(0, 0, false, " ");
    gotoxy(70, 15); log(0, 60, false, "N_");

    gotoxy(71, 15); log(0, 60, false, "E_");
    gotoxy(72, 15); log(0, 0, false, "L");

    gotoxy(58, 15); log(0, 0, false, "_              ");
    gotoxy(58, 14); log(0, 90, false, ">LIST PERSONNEL");
    gotoxy(58, 14); log(0, 0, false, "               ");
    gotoxy(58, 13); log(0, 90, false, ">LIST PERSONNEL");
    gotoxy(58, 13); log(0, 0, false, "               ");
    gotoxy(58, 12); log(0, 0, false, ">LIST PERSONNEL");

    gotoxy(58, 15); log(0, 0, false, " ");
    gotoxy(3, 6); log(0, 60, false, "_");

    gotoxy(58, 15); log(60, 0, false, "Gaut");

    gotoxy(62, 15); log(0, 0, false, "a_");
    gotoxy(3, 6); log(0, 60, false, " ");

    gotoxy(63, 15); log(0, 60, false, "m_");
    gotoxy(64, 15); log(0, 60, false, " _");
    gotoxy(65, 15); log(0, 60, false, "B_");
    gotoxy(66, 15); log(0, 60, false, "a_");

    gotoxy(67, 15); log(0, 0, false, " ");
    gotoxy(3, 6); log(0, 0, false, "_");

    gotoxy(67, 15); log(0, 60, false, "b");
    gotoxy(3, 6); log(0, 20, false, "I_");
    gotoxy(68, 15); log(0, 60, false, "b");
    gotoxy(69, 15); log(0, 20, false, "a");
    gotoxy(4, 6); log(0, 75, false, "'_");

    gotoxy(58, 15); log(0, 0, false, "             ");
    gotoxy(58, 14); log(0, 0, false, "Gautam Babbar");
    gotoxy(58, 12); log(0, 0, false, "               ");
    gotoxy(58, 11); log(0, 90, false, ">LIST PERSONNEL");

    gotoxy(5, 6); log(0, 20, false, "m_");
    gotoxy(58, 15); log(0, 0, false, "T");

    gotoxy(6, 6); log(0, 0, false, " ");
    gotoxy(59, 15); log(0, 60, false, "_");

    gotoxy(59, 15); log(0, 60, false, "e_");
    gotoxy(60, 15); log(0, 20, false, "d_");

    gotoxy(7, 6); log(0, 35, false, "m");
    gotoxy(61, 15); log(0, 35, false, " _");
    gotoxy(8, 6); log(0, 35, false, "a");
    gotoxy(62, 15); log(0, 35, false, "B_");

    gotoxy(63, 15); log(0, 35, false, " ");
    gotoxy(9, 6); log(0, 35, false, "k_");
    gotoxy(63, 15); log(0, 35, false, "a");

    gotoxy(64, 15); log(0, 0, false, "c");
    gotoxy(10, 6); log(0, 35, false, "i_");
    gotoxy(65, 15); log(0, 35, false, "k");
    gotoxy(11, 6); log(0, 35, false, "n_");
    gotoxy(66, 15); log(0, 35, false, "m");
    gotoxy(12, 6); log(0, 20, false, "g_");
    gotoxy(67, 15); log(0, 20, false, "a");

    gotoxy(13, 6); log(0, 0, false, " ");
    gotoxy(68, 15); log(0, 20, false, "_");

    gotoxy(58, 10); log(0, 0, false, ">LIST PERSONNEL");
    gotoxy(58, 13); log(0, 0, false, "Gautam Babbar");
    gotoxy(58, 14); log(0, 0, false, "Ted Backman");
    gotoxy(58, 11); log(0, 0, false, "               ");
    gotoxy(69, 14); log(0, 0, false, "  ");
    gotoxy(58, 15); log(0, 60, false, "_          ");

    gotoxy(58, 15); log(0, 35, false, "K_");
    gotoxy(14, 6); log(0, 35, false, "a");
    gotoxy(59, 15); log(0, 35, false, "e_");
    gotoxy(60, 15); log(0, 35, false, "l_");
    gotoxy(61, 15); log(0, 0, false, "l");
    gotoxy(16, 6); log(0, 35, false, "n_");
    gotoxy(62, 15); log(0, 35, false, "y");
    gotoxy(17, 6); log(0, 35, false, "o_");
    gotoxy(18, 6); log(0, 20, false, "t_");
    gotoxy(64, 15); log(0, 35, false, "B");
    gotoxy(65, 15); log(0, 20, false, "a");
    gotoxy(19, 6); log(0, 20, false, "e_");

    gotoxy(20, 6); log(0, 0, false, " ");
    gotoxy(66, 15); log(0, 20, false, "_");

    gotoxy(66, 15); log(0, 35, false, "i_");
    gotoxy(67, 15); log(0, 35, false, "l_");
    gotoxy(21, 6); log(0, 20, false, "h");
    gotoxy(68, 15); log(0, 35, false, "e_");
    gotoxy(22, 6); log(0, 0, false, "e");

    gotoxy(58, 9); log(0, 0, false, ">LIST PERSONNEL");
    gotoxy(58, 12); log(0, 0, false, "Gautam Babbar");
    gotoxy(58, 13); log(0, 0, false, "Ted Backman");
    gotoxy(58, 14); log(0, 0, false, "Kelly Bailey");
    gotoxy(58, 10); log(0, 0, false, "               ");
    gotoxy(70, 13); log(0, 0, false, " ");
    gotoxy(58, 15); log(0, 60, false, "_           ");

    gotoxy(58, 15); log(0, 20, false, "J_");

    gotoxy(23, 6); log(0, 0, false, "_");
    gotoxy(59, 15); log(0, 20, false, " ");

    gotoxy(23, 6); log(0, 20, false, "r_");
    gotoxy(59, 15); log(0, 35, false, "e");
    gotoxy(24, 6); log(0, 20, false, "e_");
    gotoxy(60, 15); log(35, 0, false, "ff");

    gotoxy(3, 7); log(0, 20, false, "_");
    gotoxy(25, 6); log(0, 75, false, ":");
    gotoxy(3, 7); log(0, 0, false, " ");
    gotoxy(63, 15); log(0, 500, false, "_");

    gotoxy(63, 15); log(0, 500, false, "B_");
    gotoxy(64, 15); log(0, 500, false, "a_");

    gotoxy(65, 15); log(0, 0, false, " ");
    gotoxy(3, 7); log(0, 500, false, "H_");

    gotoxy(65, 15); log(0, 500, false, "l");
    gotoxy(66, 15); log(0, 500, false, "l");
    gotoxy(4, 7); log(0, 500, false, "U_");
    gotoxy(67, 15); log(0, 500, false, "i");
    gotoxy(68, 15); log(0, 500, false, "n");
    gotoxy(5, 7); log(0, 500, false, "G_");
    gotoxy(69, 15); log(0, 500, false, "g");

    gotoxy(70, 15); log(0, 0, false, "_");
    gotoxy(6, 7); log(0, 500, false, " ");

    gotoxy(6, 7); log(0, 500, false, "E");
    gotoxy(70, 15); log(0, 500, false, "e_");
    gotoxy(71, 15); log(0, 500, false, "r");

    //CHANGE THE COORDINATES 1 UP
    gotoxy(58, 8); log(0, 0, false, ">LIST PERSONNEL");
    gotoxy(58, 9); log(0, 0, false, "               ");
    gotoxy(58, 11); log(0, 0, false, "Gautam Babbar");
    gotoxy(58, 12); log(0, 0, false, "Ted Backman");
    gotoxy(58, 13); log(0, 0, false, "Kelly Bailey");
    gotoxy(58, 14); log(0, 0, false, "Jeff Ballinger");
    gotoxy(58, 15); log(0, 60, false, "_             ");

#ifdef linux
    colour(0);
    colour(1);
    std::cin.get(); //!!!!!!!!!!TEMPORARY!!!!!!!!!!
#endif

#ifdef _WIN32
    std::system("color 0");
#endif

    std::cin.get();
    std::cin.get(); //!!!!!!!!!!TEMPORARY!!!!!!!!!!
    cursor(true);
}
//300 millisecond delay for blinking cursor
