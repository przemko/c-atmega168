// main.c

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <matrix8x8.h>
#include <stdlib.h>

// Conway Life:

#define DEAD(s) (s < 2 || s > 3)
#define BORN(s) (s == 3)

//#define DEAD(s) (s > 5)
//#define BORN(s) (s > 0)

int main()
{
  clock_prescale_set(clock_div_1);
  const uint8_t addr = 0x71;
  matrix8x8_init(addr);
  
  uint8_t sum[10][10];
  uint8_t cell[8][8];
  uint8_t newsum[10][10];

  for(;;)
    {
      for(uint8_t i=0; i<10; i++)
	for(uint8_t j=0; j<10; j++)
	  sum[i][j]=0;
      for(uint8_t i=0; i<8; i++)
	for(uint8_t j=0; j<8; j++)
	  cell[i][j]=0;
      
      matrix8x8_clear();
      matrix8x8_writedisplay(addr);

      for(uint8_t x=0; x<8; x++)
	for(uint8_t y=0; y<8; y++)
	  if((rand()&1) + (rand()&1) == 0)
	    {
	      cell[x][y]=1;
	      matrix8x8_drawpixel(x, y, 1);
	      for(uint8_t i=0; i<3; i++)
		for(uint8_t j=0; j<3; j++)
		  if(i != 1 || j != 1)
		    sum[x+i][y+j]++;
	    }
      matrix8x8_writedisplay(addr);
      
      for(;;)
	{
	  
	  for(uint8_t i=0; i<10; i++)
	    for(uint8_t j=0; j<10; j++)
	      newsum[i][j]=sum[i][j];
	  
	  int fixpoint = 1;
	  
	  for(uint8_t x=0; x<8; x++)
	    for(uint8_t y=0; y<8; y++)
	      if(cell[x][y])
		{
		  // zywa
		  if(DEAD(sum[x+1][y+1]))
		    {
		      // umiera
		      cell[x][y]=0;
		      fixpoint=0;
		      matrix8x8_drawpixel(x, y, 0);
		      for(uint8_t i=0; i<3; i++)
			for(uint8_t j=0; j<3; j++)
			  if(i != 1 || j != 1)
			    newsum[x+i][y+j]--;
		    }
		}
	      else
		{
		  // martwa;
		  if(BORN(sum[x+1][y+1]))
		    {
		      // rodzi sie
		      cell[x][y]=1;
		      fixpoint=0;
		      matrix8x8_drawpixel(x, y, 1);
		      for(uint8_t i=0; i<3; i++)
			for(uint8_t j=0; j<3; j++)
			  if(i != 1 || j != 1)
			    newsum[x+i][y+j]++;
		    }
		}
	  
	  for(uint8_t i=0; i<10; i++)
	    for(uint8_t j=0; j<10; j++)
	      sum[i][j]=newsum[i][j];
	  
	  matrix8x8_writedisplay(addr);
	  _delay_ms(100);
	  if(fixpoint)
	    break;
	}
    }
  return 0;
}
