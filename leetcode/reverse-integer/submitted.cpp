class Solution {
public:
    int reverse(int x) {
      bool isNegative = (x < 0);
      int number = (isNegative ? -x : x);
      int reversed = 0;

      while (number > 0) {
        if (reversed != ((reversed* 10) / 10)) return 0;

        reversed = 10 * reversed + number % 10;
        if (reversed < 0) return 0;

        number = number / 10;
      }

      return (isNegative ? -reversed : reversed);
    }
};