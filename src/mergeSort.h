std::vector<int> *auxiliarArray;
static int auxiliarSize;

// class Layout;
extern Layout layouts[total_buttons + 1];

void highlight(int &value, bool flag, int value2) {

  std::vector<int>::iterator it =
      std::find(auxiliarArray->begin(), auxiliarArray->end(), value);
  int idx1 = std::distance(auxiliarArray->begin(), it);

  it = std::find(auxiliarArray->begin(), auxiliarArray->end(), value2);
  int idx2 = std::distance(auxiliarArray->begin(), it);

  int pos_idx1 = idx1 * bar_distance;
  int pos_idx2 = idx2 * bar_distance;

  SDL_Rect idx1_ts1 = {(WindowOrientation::x_center -
                        static_cast<int>((bar_distance * auxiliarSize) / 2)) +
                           pos_idx1,
                       WindowOrientation::bottom_h - auxiliarArray->at(idx1),
                       bar_width, auxiliarArray->at(idx1)};
  SDL_Rect idx1_ts2 = {(WindowOrientation::x_center -
                        static_cast<int>((bar_distance * auxiliarSize) / 2)) +
                           pos_idx2,
                       WindowOrientation::bottom_h - auxiliarArray->at(idx2),
                       bar_width, auxiliarArray->at(idx2)};

  SDL_Rect vec[auxiliarSize] = {};
  int pos = 0;

  for (int i = 0; i < auxiliarSize; i++) {

    SDL_Rect rect = {
        (WindowOrientation::x_center - ((bar_distance * auxiliarSize) / 2)) +
            pos,
        WindowOrientation::bottom_h - auxiliarArray->at(i), bar_width,
        auxiliarArray->at(i)};
    vec[i] = std::move(rect);
    pos += bar_distance;
  }

  SDL_SetRenderDrawColor(Renderer, 0x15, 0x31, 0x4B, 0xFF);
  SDL_RenderClear(Renderer);

  for (auto layout : layouts)
    layout.render();

  SDL_SetRenderDrawColor(Renderer, 0x46, 0x82, 0xB4, 0xFF);
  SDL_RenderFillRects(Renderer, vec, auxiliarSize);

  if (flag == true) {
    SDL_SetRenderDrawColor(Renderer, 0x8A, 0x2B, 0xE2, 0xFF);
  }

  SDL_RenderFillRect(Renderer, &idx1_ts1);
  SDL_RenderFillRect(Renderer, &idx1_ts2);
  SDL_RenderPresent(Renderer);
  std::this_thread::sleep_for(std::chrono::milliseconds(8));
}

void highlight(int &value, int index = 0, bool flag = false) {

  auxiliarArray->at(index) = value;
  int idx1 = index;

  int pos_idx1 = idx1 * bar_distance;

  SDL_Rect idx1_ts1 = {(WindowOrientation::x_center -
                        static_cast<int>((bar_distance * auxiliarSize) / 2)) +
                           pos_idx1,
                       WindowOrientation::bottom_h - auxiliarArray->at(idx1),
                       bar_width, auxiliarArray->at(idx1)};

  SDL_Rect vec[auxiliarSize] = {};
  int pos = 0;

  for (int i = 0; i < auxiliarSize; i++) {

    SDL_Rect rect = {
        (WindowOrientation::x_center - ((bar_distance * auxiliarSize) / 2)) +
            pos,
        WindowOrientation::bottom_h - auxiliarArray->at(i), bar_width,
        auxiliarArray->at(i)};
    vec[i] = std::move(rect);
    pos += bar_distance;
  }

  // clear screen
  SDL_SetRenderDrawColor(Renderer, 0x15, 0x31, 0x4B, 0xFF);
  SDL_RenderClear(Renderer);

  for (auto layout : layouts)
    layout.render();

  SDL_SetRenderDrawColor(Renderer, 0x46, 0x82, 0xB4, 0xFF);
  SDL_RenderFillRects(Renderer, vec, auxiliarSize);

  if (flag) {
    SDL_SetRenderDrawColor(Renderer, 0xE6, 0xE6, 0xE6, 0xFF);
    SDL_RenderFillRect(Renderer, &idx1_ts1);
  }

  SDL_RenderPresent(Renderer);
  std::this_thread::sleep_for(std::chrono::milliseconds(8));
}

std::vector<int> merge(std::vector<int> a, std::vector<int> &tmpArray,
                       int leftPos, int rightPos, int rightEnd) {
  int leftEnd = rightPos - 1;
  int tmpPos = leftPos;
  int numElements = rightEnd - leftPos + 1;

  int start = leftPos, end = rightEnd;

  while (leftPos <= leftEnd && rightPos <= rightEnd) {
    if (a[leftPos] <= a[rightPos]) {
      highlight(a[leftPos], true, a[rightPos]);
      highlight(a[leftPos], false, a[rightPos]);
      tmpArray[tmpPos++] = std::move(a[leftPos++]);
    } else {
      highlight(a[leftPos], true, a[rightPos]);
      highlight(a[rightPos], false, a[leftPos]);
      tmpArray[tmpPos++] = std::move(a[rightPos++]);
    }
  }
  while (leftPos <= leftEnd) {
    tmpArray[tmpPos++] = std::move(a[leftPos++]);
  }
  while (rightPos <= rightEnd) {
    tmpArray[tmpPos++] = std::move(a[rightPos++]);
  }

  for (int i = 0; i < numElements; ++i, --rightEnd) {
    a[rightEnd] = std::move(tmpArray[rightEnd]);
  }

  for (int i = start; i <= end; i++) {
    highlight(a[i], i, true);
  }
  highlight(a[0], 0, false);

  return a;
}

void sort(std::vector<int> &a, std::vector<int> &tmpArray, int left,
          int right) {
  if (left < right) {
    int center = (left + right) / 2;
    sort(a, tmpArray, left, center);
    sort(a, tmpArray, center + 1, right);
    a = merge(a, tmpArray, left, center + 1, right);
  }
}
