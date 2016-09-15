/*
 * 8x8 LED array test1
 * display a line of lights moving around the perimeter of the 8x8 matrix
 *
 * www.benningtons.net
 */

// Arduino pin definitions - (ordered to keep wiring tidy)
int row[] = {14,10,4,12,9,5,8,6};    //rows - driven LOW for on
int col[] = {17,16,13,2,15,3,7,11};  //columns - driven HIGH for on

// give our moving light a tail?
int tailLen = 10;      //choose 1 to 28 to set length of traces
int tail[28];          //number of each led currently being lit
int tailPos = 0;      //current position on leading light

int i, j;		//general counters

void setup()
{
  for (i=0; i<8; i++)					//set arduino pins to be outputs
  {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }
  for (i=0; i<8; i++)					//clear the matrix display
  {
    digitalWrite(row[i], HIGH);
    digitalWrite(col[i], LOW);
  }
  for (i=0; i<=tailLen; i++) 		  //initialise the tail
  {
    tail[i]=-1;
  }
}

void loop()								// trace around the matrix perimeter
{										// address each matrix led by a number 0 to 63
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

void ledout(int i)							// routine to display the requested led
{
  tail[tailPos]=i;							// maintain a tail of leds of length tailLen
  tailPos++;
  if (tailPos >= tailLen) tailPos=0;

  for (j=0; j<tailLen; j++)
  {
    if (tail[j]>-1)
    {
      digitalWrite(row[tail[j]%8], LOW);	// translate requested led number into an x and y coordinate
      digitalWrite(col[tail[j]/8], HIGH);
      delay(2);
      digitalWrite(row[tail[j]%8], HIGH);
      digitalWrite(col[tail[j]/8], LOW);
    }
  }
}
