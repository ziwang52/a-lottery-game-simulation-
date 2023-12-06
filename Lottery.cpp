#include <iostream>
#include "graph1.h"
#include "Lottery.h"
#include<ctime>

Lottery::Lottery()
{
  int no_balls = 0;
  yourNumbers = 0;
  winningNumbers = 0;
  int matches = 0;
}
//copy of constractor practice
Lottery::Lottery(const Lottery& a)
{
  this->no_balls = a.no_balls;
  this->yourNumbers = new int[a.no_balls];
  this->winningNumbers = new int[a.no_balls];


  for (int ii = 0; ii < this->no_balls; ii++)
  {
    this->yourNumbers[ii] = a.yourNumbers[ii];
    this->winningNumbers[ii] = a.winningNumbers[ii];
  }

}
// delete dynamic array memory
Lottery::~Lottery()
{
  delete yourNumbers;
  delete winningNumbers;
}

int Lottery::getNoBalls()
{
   return no_balls;
}
//setter for no_balls
bool Lottery::setNoBalls(int no_balls)
{
  bool result = false;


  if (no_balls < 3)
  {
    no_balls = 3;
    result = false;
  }
  else if (no_balls > 10)
  {
    no_balls = 10;
    result = false;
  }
  else
  {
    this->no_balls = no_balls;
    result = true;
  }
  this->yourNumbers = new int[no_balls];
  this->winningNumbers = new int[no_balls];
return result;
}
// getter player lottery balls 
bool Lottery::addNumber(int num)
{
  bool duplicate = false;
  bool result;
  int i = 0; int j = 0;
   // prompt for player lottery nums
  for (int i = 0; i < no_balls; i++)
  {
     cout << "Enter lottery # " << i + 1 << "  <between 1 and 40>: ";
     cin >> yourNumbers[i];

      if (yourNumbers[i] < 1 || yourNumbers[i] > 40)
      {
        cout << "All numbers must be between 1 and 40 ." << endl;
        cout << "Enter lottery # " << i + 1 << " <between 1 and 40>: ";
        cin >> yourNumbers[i];
      }
     //check for duplicate
      for (j = 0; j < i; j++)
      {
          if (yourNumbers[i] == yourNumbers[j])
          {
            yourNumbers[i] = num;
            duplicate = true;
            break;
          }
       }

      if (duplicate == true)
      {
        cout << "duplicate Input - Please Reenter: ";
        cout << "Enter lottery # " << i + 1 << ": ";
        cin >> yourNumbers[i];
      }

    }

  return yourNumbers;
}

//display player lotteryballs without sorting
void Lottery::displayYourNumbers()
{
  int i = 0;

  string player_ball;

  for (i = 0; i < no_balls; i++)
  {
    //Use sprintf to combine name info
    player_ball = to_string(yourNumbers[i]) + ".bmp";
    displayBMP(player_ball, 45 * i + 40, 400);
    Sleep(1000);
  }

}
//getter for winning numbers
void Lottery::processWinningNumbers()
{

  int i = 0;
  int j = 0;
  bool duplicate = false;

  //Set the seed
  srand(time(0));

  //Generate  random numbers
  for (i = 0; i < no_balls; i++)
  {
    winningNumbers[i] = (rand() % 40 + 1);

    //Check all previous values
    do
    {
      //Set duplicate to false
      duplicate = false;

      //Check prvious values
      for (j = 0; j < i; j++)
      {
        if (winningNumbers[i] == winningNumbers[j])
        {
          winningNumbers[i] = (rand() % 40 + 1);
          duplicate = true;
          break;
        }
      }
    } while (duplicate);
    displayBMP(to_string(winningNumbers[i]) + ".bmp", 45 * i + 40, 220);
    Sleep(1000);
  }
}
//sorting player numbers
void Lottery::selectionSort()
{
  //Variable Declaration/Initialization
  int i = 0;
  int j = 0;
  int v = 0;
  string player_ball;

  // For each element after the first:
  for (i = 1; i < no_balls; i++)
  {
    // Look back through the previous (sorted) elts.
    // Insert this elt after first that is smaller,
    // moving the others up as you go by them.
    v = yourNumbers[i];

    for (j = i - 1; j >= 0 && yourNumbers[j] > v; j--)
    {
      // yourNumbers[j] is bigger; move it up
      yourNumbers[j + 1] = yourNumbers[j];
    }

    // yourNumbers[j] <= v; put v after yourNumbers[j]
    yourNumbers[j + 1] = v;
  }


  for (i = 0; i < no_balls; i++)
  {
    //Use sprintf to combine name info
    player_ball = to_string(yourNumbers[i]) + ".bmp";
    displayBMP(player_ball, 45 * i + 40, 400);
    Sleep(1000);
  }
}
// winning num sorting and display
void Lottery::insertionSort()
{
  //Variable Declaration/Initialization
  int i = 0;
  int j = 0;
  int v = 0;

  // For each element after the first:
  for (i = 1; i < no_balls; i++)
  {
    // Look back through the previous (sorted) elts.
    // Insert this elt after first that is smaller,
    // moving the others up as you go by them.
    v = winningNumbers[i];

    for (j = i - 1; j >= 0 && winningNumbers[j] > v; j--)
    {
      // winningNumbers[j] is bigger; move it up
      winningNumbers[j + 1] = winningNumbers[j];
    }

    // winningNumbers[j] <= v; put v after winningNumbers[j]
    winningNumbers[j + 1] = v;
  }
  for (i = 0; i < no_balls; i++)
  {
    displayBMP(to_string(winningNumbers[i]) + ".bmp", 45 * i + 40, 220);
    Sleep(1000);
  }
}
//return matches
int Lottery::getMatches()
{
   return matches;
}
// search for winning 
int Lottery::binarySearch( int target)
 {
  //Variable Declaration/Initialization


  for (int i =0; i<no_balls;i++)
  {
    int low = 0;
    int high = 0;
    int middle = 0;
    bool found = false;
    int index = -1;
    //Initialize low/high

    low = 0;
    high = no_balls - 1;
    target= yourNumbers[i];   
    while ((low <= high) && (!found))
    {
      middle = (low + high) / 2;

        if (winningNumbers[middle] == target)
          found = true;
        else if (target > winningNumbers[middle])
          low = middle + 1;
         else
          high = middle - 1;
     }
    // if matche is found, matches ++
      if (!found)
    {
       index = -1;
    }
      else
    {
     matches++;
    }


  }
  
  return(matches);
}
//winning computing 
int Lottery::computeWinnings()
{
  double winnings = 0.0;
  if (matches == 0)
  {
    winnings=0.0;
  }
else
{
  winnings = pow(10.0, (double)matches);
} 
 return winnings;
}