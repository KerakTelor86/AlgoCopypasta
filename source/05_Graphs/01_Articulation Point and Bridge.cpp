// gr -> adj list
// vector vis, low -> initialize to -1
// int timer -> initialize to 0
void dfs(int pos, int dad = -1) {
  vis[pos] = low[pos] = timer++;
  int kids = 0;
  for(auto& i : gr[pos]) {
    if(i == dad)
      continue;
    if(vis[i] >= 0)
      low[pos] = min(low[pos], vis[i]);
    else {
      dfs(i, pos);
      low[pos] = min(low[pos], low[i]);
      if(low[i] > vis[pos])
        is_bridge(pos, i)
        if(low[i] >= vis[pos] && dad >= 0)
          is_articulation_point(pos)
          ++kids;
    }
  }
  if(dad == -1 && kids > 1)
    is_articulation_point(pos)
  }
