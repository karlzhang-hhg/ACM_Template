1.         ��֪��point(x,y)�Ͷ����Polygon��x1,y1;x2,y2;��.xn,yn;����
2.         ��pointΪ��㣬������ԶΪ�յ���ƽ����X���ֱ��line(x,y; -��,y)��
3.         ѭ��ȡ��(for(i=0;i<n;i++))����ε�ÿһ����side(xi,yi;xi+1,yi+1)�����ж��Ƿ�ƽ����X�ᣬ���ƽ��continue������i++��
4.         ͬʱ�ж�point(x,y)�Ƿ���side�ϣ�����ǣ��򷵻�1(���ڶ������)���������������жϣ�
5.         �ж���side��line�Ƿ��н��㣬�������count++������i++��
6.         �жϽ�������������Ϊ�����򷵻�0�����ڶ�����ڣ���ż���򷵻�2�����ڶ�����⣩��
���룺
/* ���߷��жϵ�q������polygon��λ�ù�ϵ��Ҫ��polygonΪ�򵥶���Σ�������ʱ������
 ������ڶ�����ڣ� ����0
 ������ڶ���α��ϣ� ����1
 ������ڶ�����⣺ ����2
*/
const double INFINITY = 1e10;
const double ESP = 1e-5;
const int MAX_N = 1000;
 
struct Point 
{
    double x, y;
};
struct LineSegment 
{
    Point pt1, pt2;
};
typedef vector<Point> Polygon;
 
// ������ |P0P1| �� |P0P2|
double Multiply(Point p1, Point p2, Point p0)
{
    return ( (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y) );
}
// �ж��߶��Ƿ������point
bool IsOnline(Point point, LineSegment line)
{
    return( ( fabs(Multiply(line.pt1, line.pt2, point)) < ESP ) &&
    ( ( point.x - line.pt1.x ) * ( point.x - line.pt2.x ) <= 0 ) &&
    ( ( point.y - line.pt1.y ) * ( point.y - line.pt2.y ) <= 0 ) );
}
// �ж��߶��ཻ
bool Intersect(LineSegment L1, LineSegment L2)
{
    return( (max(L1.pt1.x, L1.pt2.x) >= min(L2.pt1.x, L2.pt2.x)) &&
    (max(L2.pt1.x, L2.pt2.x) >= min(L1.pt1.x, L1.pt2.x)) &&
    (max(L1.pt1.y, L1.pt2.y) >= min(L2.pt1.y, L2.pt2.y)) &&
    (max(L2.pt1.y, L2.pt2.y) >= min(L1.pt1.y, L1.pt2.y)) &&
    (Multiply(L2.pt1, L1.pt2, L1.pt1) * Multiply(L1.pt2, L2.pt2, L1.pt1) >= 0) &&
    (Multiply(L1.pt1, L2.pt2, L2.pt1) * Multiply(L2.pt2, L1.pt2, L2.pt1) >= 0)
    );
}
// �жϵ��ڶ������
bool InPolygon(const Polygon& polygon, Point point)
{
    int n = polygon.size();
    int count = 0;
    LineSegment line;
    line.pt1 = point;
    line.pt2.y = point.y;
    line.pt2.x = - INFINITY;
     
    for( int i = 0; i < n; i++ ) {
    // �õ�����ε�һ����
    LineSegment side;
    side.pt1 = polygon[i];
    side.pt2 = polygon[(i + 1) % n];
     
    if( IsOnline(point, side) ) {
    return1 ;
    }
     
    // ���sideƽ��x����������
    if( fabs(side.pt1.y - side.pt2.y) < ESP ) {
    continue;
    }
     
    if( IsOnline(side.pt1, line) ) {
    if( side.pt1.y > side.pt2.y ) count++;
    } else if( IsOnline(side.pt2, line) ) {
    if( side.pt2.y > side.pt1.y ) count++;
    } else if( Intersect(line, side) ) {
    count++;
    }
    }
     
     if ( count % 2 == 1 ) {return 0;}
    else { return 2;}
     }
 }
