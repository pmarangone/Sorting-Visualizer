void drawIndexes(std::vector<int> *vi, int vi_size, int idx1, int idx2) {
  int pos_idx1 = idx1 * bar_distance;
  int pos_idx2 = idx2 * bar_distance;

  SDL_Rect rect_index1 = {
      (WindowOrientation::x_center - ((bar_distance * vi_size) / 2)) + pos_idx1,
      WindowOrientation::bottom_h - vi->at(idx1), bar_width, vi->at(idx1)};

  SDL_Rect rect_index2 = {
      (WindowOrientation::x_center - ((bar_distance * vi_size) / 2)) + pos_idx2,
      WindowOrientation::bottom_h - vi->at(idx2), bar_width, vi->at(idx2)};

  SDL_Rect vec[vi_size] = {};
  int pos = 0;

  for (int i = 0; i < vi_size; i++) {

    SDL_Rect rect = {
        (WindowOrientation::x_center - ((bar_distance * vi_size) / 2)) + pos,
        WindowOrientation::bottom_h - vi->at(i), bar_width, vi->at(i)};
    vec[i] = std::move(rect);
    pos += bar_distance;
  }
  SDL_SetRenderDrawColor(Renderer, 0x15, 0x31, 0x4B, 0xFF);
  SDL_RenderClear(Renderer);

  for (auto layout : layouts)
    layout.render();

  SDL_SetRenderDrawColor(Renderer, 0x46, 0x82, 0xB4, 0xFF);
  SDL_RenderFillRects(Renderer, vec, vi_size);

  if (pos_idx1 != pos_idx2)
    SDL_SetRenderDrawColor(Renderer, 0x8A, 0x2B, 0xE2, 0xFF);
  else
    SDL_SetRenderDrawColor(Renderer, 0xE6, 0xE6, 0xE6, 0xFF);
  SDL_RenderFillRect(Renderer, &rect_index1);
  SDL_RenderFillRect(Renderer, &rect_index2);

  SDL_RenderPresent(Renderer);
  std::this_thread::sleep_for(std::chrono::milliseconds(8));
}

void swapRoutine(std::vector<int> &a, int rect_index1, int rect_index2) {
  drawIndexes(&a, array_size, rect_index1, rect_index2);
  std::swap(a[rect_index1], a[rect_index2]);
  drawIndexes(&a, array_size, rect_index2, rect_index1);
}

const int partition(std::vector<int> &arr, int low, int high) {
  const int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= pivot) {
      i++;
      swapRoutine(arr, i, j);
    }
  }
  swapRoutine(arr, i + 1, high);
  return (i + 1);
}

void quickSortRoutine(std::vector<int> &arr, int left, int right) {
  if (left < right) {
    const int pivot = partition(arr, left, right);
    quickSortRoutine(arr, left, pivot - 1);
    quickSortRoutine(arr, pivot + 1, right);
  }
}
