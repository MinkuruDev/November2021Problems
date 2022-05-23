#include <bits/stdc++.h>
#define vti vector<int>
using namespace std;

// global variable
vti a;
int blockSize, blockCount;

struct Block{
    int low, high, numberOfDiffirent, localMax;
    vti amount;
};

void logBlock(Block block){
    cout << block.low << " " << block.high << endl;
    cout << block.localMax<< endl;
    int blockSize = block.amount.size();
    for(int i = 0; i<blockSize; i++){
        cout << block.amount[i] << " ";
    }
    cout << endl;
}

int findMax(Block blocks[], int l, int r){
    int leftIndex = l/blockSize;
    int rightIndex = r/blockSize;
    int M = -INFINITY, continiuos = 0;

    for(int i = leftIndex + 1; i<rightIndex; i++){
        M = M > blocks[i].localMax? M : blocks[i].localMax;
        if(i == leftIndex + 1) continue;

        if(a[blocks[i-1].high] == a[blocks[i].low]){
            int temp = blocks[i-1].amount.back() + blocks[i].amount.front();
            M = M > temp? M: temp;
            if(block[i - 1].localMax == blockSize) {

            }
        }
    }

    return M;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    blockSize = round(sqrt(n));
    blockCount = ceil((float)n/blockSize);
    Block blocks[blockCount];
    //cout << blockCount;

    int previous, current;

    for(int i = 0; i < blockCount - 1; i++){
        cin >> previous;
        a.push_back(previous);

        blocks[i].amount.push_back(1);
        blocks[i].low = i*blockSize;
        blocks[i].high = (i+1)*blockSize-1;
        blocks[i].numberOfDiffirent = 1;

        int M = blocks[i].amount.back();
        blocks[i].localMax = M;

        int countNumber = 1;
        while(++countNumber <= blockSize){
            cin >> current;
            a.push_back(current);

            if(current == previous){
                auto it = blocks[i].amount.end();
                ++(*(--it));
            }else{
                blocks[i].amount.push_back(1);
                blocks[i].numberOfDiffirent++;
            }

            M = M > blocks[i].amount.back() ? M : blocks[i].amount.back();
            previous = current;
        }

        blocks[i].localMax = M;
        countNumber = 0;
    }

    int surplus = n % blockSize;
    if (surplus == 0) surplus = blockSize;
    Block lastBlock = blocks[blockCount-1];
    cin >> previous;
    a.push_back(previous);

    lastBlock.amount.push_back(1);
    lastBlock.low = (blockCount-1)*blockSize;
    lastBlock.high = lastBlock.low + surplus - 1;
    lastBlock.numberOfDiffirent = 1;

    int M = lastBlock.amount.back();
    lastBlock.localMax = M;

    for(int i = 1; i < surplus; i++){
        cin >> current;
        a.push_back(current);

        if(current == previous){
            auto it = lastBlock.amount.end();
            ++(*(--it));
        }else{
            lastBlock.amount.push_back(1);
            lastBlock.numberOfDiffirent++;
        }

        M > lastBlock.amount.back() ? M : lastBlock.amount.back();
        previous = current;
    }

    lastBlock.localMax = M;
    blocks[blockCount-1] = lastBlock;

    for(int i = 0; i<blockCount; i++){
        cout << "Block #" << i << ":\n";
        logBlock(blocks[i]);
    }

    return 0;
}

