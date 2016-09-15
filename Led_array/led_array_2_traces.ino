/*
 * 8x8 LED array test2
 * display a line of lights moving around the perimeter of the 8x8 matrix
 * display a 2nd line of lights moving around an inner 4x4 set of LEDs
 *
 * www.benningtons.net
 */

// Arduino pin definitions - (ordered to keep wiring tidy)
int row[] = {14,10,4,12,9,5,8,6};    //rows - driven LOW for on
int col[] = {17,16,13,2,15,3,7,11};  //columns - driven HIGH for on

// give our moving light a tail?
int tailLen = 10;      //choose 1 to 30 to set length of traces
int tail[30];          //number of each led currently being lit
int tailPos = 0;      //current position on leading light

int i, j;		//general counters

void setup()
{
  for (i=0; i<8; i++) 				 //set arduino pins to be outputs
  {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }
  for (i=0; i<8; i++) 	             //clear
  {
    digitalWrite(row[i], HIGH);
    digitalWrite(col[i], LOW);
  }
  for (i=0; i<=tailLen; i++) 		  //initialise the tail
  {
    tail[i]=-1;
  }
}

void loop()							// address each led in the matrix as 0 to 63
{
    for (i=0; i<8; i++)
    {
      ledout(i);
    }
    for (i=15; i<56; i=i+8)
    {
      ledout(i);
    }
    for (i=63; i>55; i--)
    {
      ledout(i);
    }
    for (i=48; i>0; i=i-8)
    {
      ledout(i);
    }
}

void ledout(int i)
{
  tail[tailPos]=i;
  tailPos++;
  if (tailPos >= tailLen) tailPos=0;		// variable length tail

  for (j=0; j<tailLen; j++)
  {
    if (tail[j]>-1)
    {
      digitalWrite(row[tail[j]%8], LOW);	// translate each led address into x and y coordinates
      digitalWrite(col[tail[j]/8], HIGH);
      delay(2);
      digitalWrite(row[tail[j]%8], HIGH);
      digitalWrite(col[tail[j]/8], LOW);
    }
  }
}
