#include<iostream>
#include<stack>
#include<stdlib.h>
#include<string.h>
#include<vector>

using namespace std;

struct loc_t { int r, c; };

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
  int cr = rand() % rows;
  int cc = rand() % cols;
  int cvs = 1;

  stack<loc_t> locs;
  int ofr[] = { 0, 1, 0, -1 };
  int ofc[] = { -1, 0, 1, 0 };

  while(cvs < n)
  {
    vector<int> chocs;
    for(int i = 0; i < 4; i++)
    {
      int crp = cr + ofr[i];
      int ccp = cc + ofc[i];
      if (crp >= 0 && crp < rows && ccp >= 0 && ccp < cols)
      {
        if (maze[crp * cols + ccp] == 0x0F) { chocs.push_back(i); }
      }
    }

    if (chocs.empty())
    {
      loc_t &l = locs.top();
      cr = l.r;
      cc = l.c;
      locs.pop();
    }
    else
    {
      loc_t l;
      l.r = cr;
      l.c = cc;
      locs.push(l);

      int i = rand() % chocs.size();
      int ind = chocs[i];

      if (ofr[ind] > 0)
      {
        maze[cr * cols + cc] &= 0x0D;
        maze[(cr + ofr[ind]) * cols + (cc + ofc[ind])] &= 0x07;
      }
      else if (ofr[ind] < 0)
      {
        maze[cr * cols + cc] &= 0x07;
        maze[(cr + ofr[ind]) * cols + (cc + ofc[ind])] &= 0x0D;
      }
      else if (ofc[ind] < 0)
      {
        maze[cr * cols + cc] &= 0x0E;
        maze[(cr + ofr[ind]) * cols + (cc + ofc[ind])] &= 0x0B;
      }
      else
      {
        maze[cr * cols + cc] &= 0x0B;
        maze[(cr + ofr[ind]) * cols + (cc + ofc[ind])] &= 0x0E;
      }

      cr += ofr[ind];
      cc += ofc[ind];

      cvs++;
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

