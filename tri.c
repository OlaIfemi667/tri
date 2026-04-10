#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define HOW_MANY 500 //  how many histograms



typedef struct
{
	Color color;
	float height;
  int position;
} Histogram;

//prototypes
void InitHistogram(Histogram *histograms);
void DrawInit(Histogram *histograms);
int checkLonger(Histogram hist_a, Histogram hist_b);
void moveHistogram(Histogram *histogram, float position_x);

void InitHistogram(Histogram *histograms)
{
  SetRandomSeed(time(NULL));

  for (int i = 0; i < HOW_MANY; i++)
  {
    histograms[i].color = WHITE;
    histograms[i].height = GetRandomValue(0, HEIGHT - 100);
    histograms [i].position = i + 1;
  }
}


/* DrawInit - Draw
 * histograms - histogram buffer
 * Return - void
 */
void DrawInit(Histogram *histograms)
{
  for (int i = 0; i < HOW_MANY; i++)
  {
    float position_x = histograms[i].position * (WIDTH - 100) / HOW_MANY;

    DrawRectangle(position_x, HEIGHT - histograms[i].height - 50, HEIGHT / HOW_MANY, histograms[i].height, histograms[i].color);
  }
}


/** checkLonger - check the longer histogram
 * hist_a -  first histogram
 * hist_b - second histogram
 * Return: 0 if hist_a longer and 0 if not
 */
int checkLonger(Histogram hist_a, Histogram hist_b)
{
  if (hist_a.height > hist_b.height)
    return 0;
  else
    return 1;
}



/* moveHistogram - deplacer l'histogram
 * histogram - histogram
 * position_x - position
 * Return: void
 */
void moveHistogram(Histogram *histogram, float position_x)
{
  DrawRectangle(position_x, HEIGHT - histogram->height - 50, HEIGHT / HOW_MANY, histogram->height, histogram->color);

}

/** tri - fonction de Tri
 * histograms - le tableau des histograms
 * Return: void
 */
int tri(Histogram *histograms)
{
  // nous voulons comparer la valeur actuelle dans la loop a la suivant 
  // pour eviter les seg fault il faut donc que i < HOW_MANY - 1
  for(int i = 0; i < HOW_MANY - 1; i++)
  {
    Histogram temp;
    if (checkLonger(histograms[i], histograms[i+1]) == 0)
    {
      temp = histograms[i+1];
      histograms[i+1] = histograms[i];
      histograms[i] = temp;
      histograms[i].position = i + 1;
      histograms[i+1].position = i + 2;
    } 
  }
}


/** main - tri fusion
 *  Return: 0 on successs
*/
int main()
{
	InitWindow(WIDTH, HEIGHT, "Tri Fusion");
	Histogram *histograms = (Histogram *) malloc(sizeof(Histogram) * HOW_MANY);
  InitHistogram(histograms);
  SetTargetFPS(30);
	while (!WindowShouldClose())
	{
		BeginDrawing();
      DrawFPS(10, 10);
			ClearBackground(BLACK);
      DrawInit(histograms);
      tri(histograms);
      WaitTime(0.5);
		EndDrawing();
  }
}
