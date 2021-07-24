#include <bits/stdc++.h>
using namespace std;
#define MAX_N 10000

typedef long long ll;

int N;
struct Point{
    ll x, y;
    Point(ll a, ll b) : x(a), y(b){}
    Point() {}
    bool operator < (const Point &p) const {
        if(x != p.x) return x < p.x;
        return y < p.y;
    }
} P[MAX_N];

int ccw(Point a, Point b, Point c){
    ll tmp = a.x*b.y + b.x*c.y + c.x*a.y;
    tmp -= b.x*a.y + c.x*b.y + a.x*c.y;
    return (tmp>0)-(tmp<0);
}

bool chk(Point a, Point b, Point c, Point d){
	Point t = {b.x - a.x, b.y - a.y};
	Point tt = {d.x - c.x, d.y - c.y};
	return ccw({0,0}, t, tt) >= 0;
}

ll dist(Point p, Point q){
    return (p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y);
}


ll rotating_calipers(){
    for(int i=1; i<N; ++i){
        if(P[i] < P[0]) swap(P[0], P[i]);
    }

    // Convex Hull
    vector<Point> hull;
	sort(P+1, P+N, [](Point &a, Point &b){
		int cw = ccw(P[0], a, b);
		if(cw) return cw > 0;
		return dist(P[0], a) < dist(P[0], b);
	});
	for(int i=0; i<N; ++i){
		while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), P[i]) <= 0){
			hull.pop_back();
		}
		hull.push_back(P[i]);
	}

	int pt = 0;
	ll ret = 0;
	for(int i=0; i<hull.size(); i++){
		while(pt+1 < hull.size() && chk(hull[i], hull[i+1], hull[pt], hull[pt+1])){
			ret = max(ret, dist(hull[i], hull[pt])); ++pt;
		}
		ret = max(ret, dist(hull[i], hull[pt]));
	}

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for(int i=0; i<N; ++i){
        cin >> P[i].x >> P[i].y;
    }

    // Returns the maximum distance of two points in P[0:N-1]
    cout << rotating_calipers();
}
