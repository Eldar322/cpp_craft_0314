#include <stdio.h>
#include <set>

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	long n;
	double d;
	std::set <long> codes;
	scanf("%ld", &n);
	for (long i = 0; i < n; i++)
	{
		scanf("%lf", &d);
		codes.insert(floor(d*10000));
	}
	while (! std::feof(stdin))
	{
		scanf("%lf", &d);
		if (codes.find(floor(d*10000)) != codes.end())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}