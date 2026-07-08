#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper)
            ? enWinner::Computer : enWinner::Player;

    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            ? enWinner::Computer : enWinner::Player;

    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone)
            ? enWinner::Computer : enWinner::Player;
    }

    return enWinner::Draw;
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] =
    {
        "Player1",
        "Computer",
        "No Winner (Draw)"
    };

    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayerChoice()
{
    short Choice;

    do
    {
        cout << "\nYour Choice: [1] Stone, [2] Paper, [3] Scissors : ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    if (RoundInfo.Winner == enWinner::Player)
    {
        system("color 2F");
    }
    else if (RoundInfo.Winner == enWinner::Computer)
    {
        system("color 4F");
        cout << "\a";
    }
    else
    {
        system("color 6F");
    }

    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player Choice   : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner    : " << RoundInfo.WinnerName << endl;

    cout << "\n____________________________________________\n";

    system("color 07");
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    stGameResults GameResults;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] Begins\n";

        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();

        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
            GameResults.PlayerWinTimes++;

        else if (RoundInfo.Winner == enWinner::Computer)
            GameResults.ComputerWinTimes++;

        else
            GameResults.DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    GameResults.GameRounds = HowManyRounds;

    GameResults.GameWinner =
        WhoWonTheGame(
            GameResults.PlayerWinTimes,
            GameResults.ComputerWinTimes);

    GameResults.WinnerName =
        WinnerName(GameResults.GameWinner);

    return GameResults;
}
void PrintFinalGameResults(stGameResults GameResults)
{
    if (GameResults.GameWinner == enWinner::Player)
    {
        system("color 2F");
    }
    else if (GameResults.GameWinner == enWinner::Computer)
    {
        system("color 4F");
        cout << "\a";
    }
    else
    {
        system("color 6F");
    }

    cout << "\n\n==========================================\n";
    cout << "             GAME OVER\n";
    cout << "==========================================\n";

    cout << "\nGame Rounds      : " << GameResults.GameRounds;
    cout << "\nPlayer Wins      : " << GameResults.PlayerWinTimes;
    cout << "\nComputer Wins    : " << GameResults.ComputerWinTimes;
    cout << "\nDraw Times       : " << GameResults.DrawTimes;
    cout << "\nFinal Winner     : " << GameResults.WinnerName << endl;

    cout << "\n==========================================\n";

    system("color 07");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");

        short HowManyRounds;

        do
        {
            cout << "How many rounds do you want to play (1-10)? ";
            cin >> HowManyRounds;

        } while (HowManyRounds < 1 || HowManyRounds > 10);

        stGameResults GameResults = PlayGame(HowManyRounds);

        PrintFinalGameResults(GameResults);

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}