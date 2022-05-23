#include <bits/stdc++.h>
#define vti vector<int>
#define pii pair<int,int>
#define repeat(i,a,b) for(int i = a; i<b; i++)

using namespace std;

class Node{
    public:
        pii head, tail;
        int localMax;

        Node(){
            localMax = 0;
        }

        Node(int k){
            head = make_pair(k, 1);
            tail = make_pair(k, 1);
            localMax = 1;
        }

        Node operator+(const Node other){
            if(other.localMax == 0) return *this;
            if(this->localMax == 0) return other;

            Node result;
            result.head = this->head;
            result.tail = other.tail;

            if(this->head.first == other.head.first){
                result.head.second = this->head.second + other.head.second;
            }
            if(this->tail.first == other.tail.first){
                result.tail.second = other.tail.second + this->tail.second;
            }
            int temp = 0;
            if(this->tail.first == other.head.first){
                temp = this->tail.second + other.head.second;
            }
            result.localMax = max(max(localMax, other.localMax), max(temp, max(result.head.second, result.tail.second)));

            return result;
        }
};

class SegmentTree{
    private:
        static const int MAX_SIZE = 5000;
        Node ST[MAX_SIZE*4];
        int lazy[MAX_SIZE*4];
        vti buildArr;
        int sz;
        void build(int id, int low, int high){
            if(low == high){
                ST[id] = Node(buildArr[low]);
                //printf("\nBuilding %d %d %d\n", id, low, high);
                //printf("%d %d    %d     %d %d\n", ST[id].head.first, ST[id].head.second,
                       //ST[id].localMax, ST[id].tail.first, ST[id].tail.second);
                return;
            }

            int mid = (low + high) >> 1;
            int id2 = id << 1;
            build(id2, low, mid);
            build(id2+1, mid+1, high);

            // ST[id] = max(ST[id2], ST[id2+1]);
            ST[id] = ST[id2] + ST[id2+1];
            //printf("\nBuilding %d %d %d\n", id, low, high);
            //printf("%d %d    %d     %d %d\n", ST[id].head.first, ST[id].head.second,
                    //ST[id].localMax, ST[id].tail.first, ST[id].tail.second);
        }

    public:
        SegmentTree(){
            sz = MAX_SIZE;
        }

        SegmentTree(int sz){
            this->sz = sz;
        }

        SegmentTree(vti initArr){
            sz = initArr.size() - 1;
            buildArr = initArr;

            build(1,1,sz);
        }

        Node get(int id, int low, int high, int left, int right){
            if(low > right || high < left) return Node(); // for sum or max of positive int
            // if(low > right || high < left) return -(int)INFINITY; // for max only
            //printf("getting %d %d %d\n", id, low, high);

            if(low >= left && high <=right){
                return ST[id];
            }

            // down(id)

            int mid = ((low + high) >> 1);
            int id2 = id << 1;

            /// down
            // return max(get(id2, low, mid, left, right),
            //            get(id2+1, mid+1, high, left, right));
            return get(id2, low, mid, left, right) + get(id2+1, mid+1, high, left, right);

            /// not down
            // return max(get(id2, low, mid, left, right),
               //         get(id2+1, mid+1, high, left, right)) + lazy[id];
            // return ST[id] + (low-high+1) * lazy[id]
        }

};

vti generateRandom(int n = 20, int range = 6){
    vti result;
    srand(time(0));
    while(n--){
        int temp = rand()%range;
        if(rand()%2) temp = -temp;
        result.push_back(temp);
    }

    sort(result.begin(), result.end());
    return result;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,q;
    cin >> n >> q;
    vti a;
    a.push_back(0);
    vti ran = generateRandom(n);
    a.insert(a.end(), ran.begin(), ran.end());

    repeat(i,0,n){
        cout << a[i+1] << " ";
    }
    cout << endl;

    SegmentTree st(a);

    int l,r;
    while(q--){
        cin >> l >> r;
        cout << st.get(1,1,n,l,r).localMax << endl;
    }

    cin >> q;

    return 0;
}

