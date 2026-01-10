#pragma once

template<typename Indices, typename... Objects>
  requires std::random_access_iterator<std::remove_reference_t<Indices>>
        || std::is_pointer_v<std::remove_reference_t<Indices>>
void apply_permutation(
  const size_t begin, const size_t end, Indices indices, Objects... objects) {
  using std::swap;
  for (size_t i = begin; i < end; i++) {
    auto current = i;
    // while there's a cycle (‘indices[current]’ doesn’t point to ‘i’ - its
    // current offset/position)
    while (i != indices[current - begin]) {
      // store the index which should be in the current position
      const auto next = indices[current - begin];
      // swap ‘next’ with ‘current’ – ‘next’ is now where it should be
      ([&](const auto it) { swap(it[current], it[next]); }(objects), ...);
      // write ‘current’ to current position in indices (current position and
      // ‘indices[current]’ match)
      indices[current - begin] = current;
      // move to next index in the cycle
      current = next;
    }
    // when cycle is reached, write ‘current’ to current position in indices
    // (ensures earlier swapped value has the correct index in indices)
    indices[current - begin] = current;
  }
}

template<typename Indices, typename... Objects>
  requires std::random_access_iterator<std::remove_reference_t<Indices>>
        || std::is_pointer_v<std::remove_reference_t<Indices>>
void apply_inverse_permutation(
  const size_t begin, const size_t end, Indices indices, Objects... objects) {
  using std::swap;
  for (size_t i = begin; i < end; i++) {
    // while 'indices[i]' is not in the correct position/matches its offset
    while (i != indices[i - begin]) {
      // look-up where the current index/object should be
      const auto next = indices[i - begin];
      // swap the object/index to move them to the correct final position
      // move what was in that slot to the current position
      ([&](const auto it) { swap(it[i], it[next]); }(objects), ...);
      swap(indices[i - begin], indices[next - begin]);
    }
  }
}
