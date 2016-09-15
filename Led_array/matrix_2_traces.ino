/*
 * 8x8 led array testing - see led_testing.fzz
 * If wiring appears ok but still not working try turning the matrix around
 * or reversing all the high/low logic in this code.
 *
 * Display a snake of variable tail length moving around the matrix perimeter
 *	and another moving in the opposite direction around the inner 4x4 leds
 * But instead of using the vector approach of illuminating each individual led
 *  we'll use the raster approach of mapping the snakes and then displaying a
 *  line at a time.
 *
 * www.benningtons.net
 */

// Arduino pin definitions - (ordered to keep wiring tidy)
int rowPin[] = {14,10,4,12,9,5,8,6};    //rows - driven LOW for on
int colPin[] = {17,16,13,2,15,3,7,11};  //columns - driven HIGH for on

// give our moving light a tail?
int tailLen = 30;      // choose 2 to 54 to set length of traces
int tail[54];          // number of each led currently being lit
int tailPos = 0;      // current position on leading light

// a logic array to map 8x8 led matrix - #todo convert to binary
int ledMatrix[64];

void setup()
{
  for (int i=0; i<8; i++)        //set arduino pins to be outputs
  {
    pinMode(rowPin[i], OUTPUT);
    pinMode(colPin[i], OUTPUT);
  }

  for (int i=0; i<8; i++)            //clear the led matrix
  {
    digitalWrite(rowPin[i], HIGH);
    digitalWrite(colPin[i], LOW);
  }

  for (int i=0; i<=tailLen; i++)     //initialise tail
  {
    tail[i]=-1;
  }

  for (int i=0; i<64; i++)      // clear matrix array map
  {
    ledMatrix[i]=0;
  }
}

void loop()
{
    for (int i=0; i<8; i++)                    //race around
    {
      ledout(i);                   //Trace 1 - outer 8x8 leds - clockwise
//      ledout((i/2)+18);            //Trace 2 - inner 4x4 leds - clockwise
      ledout(42+(i/2));            // Trace 2 - inner 4x4 leds - anti-clockwise
    }

    for (int i=15; i<56; i=i+8)
    {
      ledout(i);
//      ledout(((i/16)*8)+21);
      ledout(45-((i/16)*8));
    }

    for (int i=63; i>55; i--)
    {
      ledout(i);
//      ledout(((i-63)/2)+45);
      ledout(18+((i-56)/2));
    }

    for (int i=48; i>0; i=i-8)
    {
      ledout(i);
//      ledout(((i/16)*8)+18);
      ledout(42-((i/16)*8));
    }
}

void ledout(int i)                    //light requested led + variable tail of previous leds
{
  if (tail[tailPos] > -1) ledMatrix[tail[tailPos]]=0;  // mark end of tail led to be turned off 
  tail[tailPos]=i;
  tailPos++;
  if (tailPos >= tailLen) tailPos=0;
  ledMatrix[i]=1;

  for (int j=0; j<8; j++)            //for each column
  {
    for (int k=0; k<8; k++)            //turn off all rows
    {
      digitalWrite(rowPin[k], HIGH);
    }

    for (int k=0; k<8; k++)            //turn off all columns except current column
    {
      if (k==j)
      {
        digitalWrite(colPin[k], HIGH);
      }
      else
      {
        digitalWrite(colPin[k], LOW);
      }
    }

    for (int k=0; k<8; k++)            //turn on required leds in current row
    {
      if (ledMatrix[((j*8)+k)]==1)
      {
        digitalWrite(rowPin[k], LOW);
      }
    }
    delay(3);
  }
}



