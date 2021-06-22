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
  memset(maze, 0x1F, rows * cols * sizeof(unsigned char));

  srand(time(NULL));
  int cr = rand() % rows;
  int cc = rand() % cols;
  int cvs = 0;

  int ofr[] = { 0, 1, 0, -1 };
  int ofc[] = { -1, 0, 1, 0 };

  while(cvs < n)
  {
    int ind = rand() % 4;
    int nr = cr + ofr[ind];
    int nc = cc + ofc[ind];

    if (nr < 0) nr++;
    if (nr >= rows) nr--;

    if (nc < 0) nc++;
    if (nc >= cols) nc--;

    if (maze[nr * cols + nc] & 0x10)
    {
      maze[nr * cols + nc] &= 0x0F;

      if (ofr[ind] > 0)
      {
        maze[cr * cols + cc] &= 0xFD;
        maze[nr * cols + nc] &= 0xF7;
      }
      else if (ofr[ind] < 0)
      {
        maze[cr * cols + cc] &= 0xF7;
        maze[nr * cols + nc] &= 0xFD;
      }
      else if (ofc[ind] < 0)
      {
        maze[cr * cols + cc] &= 0xFE;
        maze[nr * cols + nc] &= 0xFB;
      }
      else
      {
        maze[cr * cols + cc] &= 0xFB;
        maze[nr * cols + nc] &= 0xFE;
      }

      cvs++;
    }

    cr = nr;
    cc = nc;
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

for(int i = 0; i < s * cols; i++)
{
  img[i] = 0;
}

for(int i = 0; i < s * rows; i++)
{
  img[i * s * cols] = 0;
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

