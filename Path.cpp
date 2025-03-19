#include "Complex.h"
#include "Path.h"
#include <cmath>
#include <vector>

float threashold = .5f;

using namespace std;

shape::shape(int x, int y){
    start = new Path(x,y,N);
    end = start;
    N++;
}
Path::~Path() {
    // Remove `delete prev;` and `delete next;`
}

shape::~shape() {
    Path* current = start;
    while (current != nullptr) {
        Path* next = current->next;
        delete current;  // Now we are only deleting once
        current = next;
    }
    start = nullptr;
}

float pointDis(int px, int py,int x1,int y1,int x2,int y2){
    if (x1 == x2 && y1 == y2) {
        return sqrt((px - x1) * (px - x1) + (py - y1) * (py - y1));
    }
      return abs((y2 - y1) * px - (x2 - x1) * py + x2 * y1 - y2 * x1)/sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));

}
void shape::RDP(Path* S, Path* end) {
    if (!S || !end || S == end) return;

    Path* farthest = nullptr;
    float maxDist = 0;
    Path* current = S->next;

    while (current && current != end) {
        float dist = pointDis(current->x, current->y, S->x, S->y, end->x, end->y);
        if (dist > maxDist) {
            maxDist = dist;
            farthest = current;
        }
        current = current->next;
    }

    if (maxDist > threashold) {
        RDP(S, farthest);
        RDP(farthest, end);
    } else {
        vector<Path*> toDelete;
        current = S->next;
        while (current && current != end) {
            toDelete.push_back(current);
            current = current->next;
        }
        for (Path* p : toDelete) {
            delete p;
        }
        S->next = end;
        end->prev = S;
    }
}

void shape::SimplifyPath(){
    RDP(start,end);
};//RDP Rammer-Doglas-Peucker

void shape::add(int x, int y){
    Path* newPath = new Path(x, y, N);
    end->next = newPath;
    newPath->prev = end;
    end = newPath;
}
