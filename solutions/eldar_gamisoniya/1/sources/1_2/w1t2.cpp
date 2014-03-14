#include <stdio.h>
#include <set>

int main()
{
	freopen(BINARY_DIR"/input.txt", "r", stdin);
	freopen(SOURCE_DIR"/output.txt", "w", stdout);
	long n;
	long double d;
	std::set <long long> codes;
	scanf("%ld", &n);
	for (long i = 0; i < n; i++)
	{
		scanf("%lf", &d);
		codes.insert((long long) (d*10000));
	}
	while (! std::feof(stdin))
	{
		scanf("%lf", &d);
		if (codes.find((long long)(d*10000)) != codes.end())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}