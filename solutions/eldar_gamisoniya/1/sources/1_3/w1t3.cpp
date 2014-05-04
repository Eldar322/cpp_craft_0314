#include <queue>
#include <vector>
#include <string>
#include <iostream>

typedef std::vector < std::pair < std::string, std::vector <bool> > > map_n_comp;

void bfs(map_n_comp & map,const size_t n,const size_t m,const int startx,const int starty)
{
	const std::pair <int, int> dir [4] = {std::make_pair(-1, 0), std::make_pair(1, 0),
		std::make_pair(0, -1), std::make_pair(0, 1)};
	int x, y;
	std::queue <std::pair <int, int> > q;
	map[startx].second[starty] = true;
	q.push(std::make_pair(startx, starty));
	while (!q.empty())
	{
		for (int i = 0; i < 4; i++)
		{
			x = q.front().first + dir[i].first;
			y = q.front().second + dir[i].second;
			if (x >= 0 && x < n && y >= 0 && y < m && map[x].first[y] == 'o' && map[x].second[y] == false)
			{
				map[x].second[y] = true;
				q.push(std::make_pair(x, y));
			}
		}
		q.pop();
	}
}

int main()
{
	freopen(BINARY_DIR"/input.txt", "r", stdin);
	freopen(BINARY_DIR"/output.txt", "w", stdout);
	map_n_comp map;
	std::string s;
	size_t n, m = 0;
	std::vector <bool> v;
	for (n = 0; std::getline(std::cin, s); n++)
	{
		if (n == 0){
			m = s.length();
			v = std::vector <bool> (m, false);
		}
		map.push_back(std::make_pair(s, v));
	}
	int k = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (map[i].first[j] == 'o' && map[i].second[j] == false)
			{
				k++;
				bfs(map, n, m, i, j);
			}
	std::cout << k;
	return 0;
}