#include<iostream>
#include<stack>
#include<stdlib.h>
#include<string.h>
#include<vector>

using namespace std;

void mrec(int ir, int ic, int lr, int lc, int rows, int cols, unsigned char *m)
{
  if (lr - ir < 1 || lc - ic < 1) return;

  int rr = rand() % (lr - ir) + ir;
  int rc = rand() % (lc - ic) + ic;

  for(int c = ic; c <= lc; c++) { m[rr * cols + c] |= 0x02; }
  for(int r = ir; r <= lr; r++) { m[r * cols + rc] |= 0x04; }

  int rcp = rand() % (rc - ic + 1) + ic;
  m[rr * cols + rcp] &= 0x0D;

  rcp = rand() % (lc - rc) + rc + 1;
  m[rr * cols + rcp] &= 0x0D;

  int rrp = rand() % (lr - rr) + rr + 1;
  m[rrp * cols + rc] &= 0x0B;

  mrec(ir, ic, rr, rc, rows, cols, m);
  mrec(rr+1, ic, lr, rc, rows, cols, m);
  mrec(ir, rc+1, rr, lc, rows, cols, m);
  mrec(rr+1, rc+1, lr, lc, rows, cols, m);
}

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
  memset(maze, 0x00, rows * cols * sizeof(unsigned char));

  srand(time(NULL));
  mrec(0, 0, rows - 1, cols - 1, rows, cols, maze);

unsigned char *img = new unsigned char[s * s * cols * rows];
memset(img, 1, s * s * cols * rows);
for(int r = 0; r < rows; r++)
{
  for(int c = 0; c < cols; c++)
  {
    unsigned char v = maze[r * cols + c];
    int rp = s * r;
    int cp = s * c;

    if (v & 0x02)
    {
      for(int i = 0; i <= s; i++)
      {
        img[(rp + s) * s * cols + (cp + i)] = 0;
      }
    }

    if (v & 0x04)
    {
      for(int i = 0; i < s; i++)
      {
        img[(rp+i) * s * cols + cp + s] = 0;
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

