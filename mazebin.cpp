#include<iostream>
#include<stack>
#include<stdlib.h>
#include<string.h>
#include<vector>

using namespace std;

int main(int argc, char **argv)
{
  if (argc != 3 && argc != 4)
  {
    cerr << "Usage: " << argv[0] << " <rows> <cols> [cell size]" << endl;
    return(1);
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);

  int s = 10;
  if (argc == 4) s = atoi(argv[3]);

  int n = rows * cols;
  unsigned char *maze = new unsigned char[n];
  memset(maze, 0x0F, rows * cols * sizeof(unsigned char));

  srand(time(NULL));
  for(int r = 0; r < rows; r++)
  {
    for(int c = 0; c < cols; c++)
    {
      if (rand() % 2)
      {
        maze[r * cols + c] &= 0x0D;
        if (r < rows - 1) maze[(r + 1) * cols + c] &= 0x07;
      }
      else
      {
        maze[r * cols + c] &= 0x0B;
        if (c < cols - 1) maze[r * cols + c + 1] &= 0x0E;
      }

      if (r == rows - 1)
      {
        maze[r * cols + c] &= 0x0B;
        if (c < cols - 1) maze[r * cols + c + 1] &= 0x0E;
      }

      if (c == cols - 1)
      {
        maze[r * cols + c] &= 0x0D;
        if (r < rows - 1) maze[(r + 1) * cols + c] &= 0x07;
      }
    }
  }

unsigned char *img = new unsigned char[s * s * cols * rows];
memset(img, 1, s * s * cols * rows);
for(int r = 0; r < rows; r++)
{
  for(int c = 0; c < cols; c++)
  {
    unsigned char v = maze[r * cols + c];
    int rp = s * r;
    int cp = s * c;

    if (v & 0x01)
    {
      for(int i = 0; i < s; i++)
      {
        img[(rp+i) * s * cols + cp] = 0;
      }
    }

    if (v & 0x08)
    {
      for(int i = 0; i <= s; i++)
      {
        img[rp * s * cols + (cp + i)] = 0;
      }
    }
  }
}

for(int i = 0; i < s * rows; i++)
{
  img[i * s * cols + s * cols - 1] = 0;
}

for(int i = 0; i < s * cols; i++)
{
  img[(s * rows - 1) * s * cols + i] = 0;
}

cout << "P2" << endl << s * cols << " " << s * rows << endl << "1" << endl;
for(int r = 0; r < s * rows; r++)
{
  for(int c = 0; c < s * cols; c++)
  {
    cout << (int)img[r * s * cols + c] << " ";
  }
}

  delete [] img;
  delete [] maze;

  return(0);
}

