#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::vector;

class Team {
 public:
  explicit Team(const vector<int>& height) {
    transform(begin(height), end(height), back_inserter(players_),
              [](int h) { return Player{h}; });
  }

  // Checks if team0 can be placed in front of team1.
  static bool ValidPlacementExists(const Team& team0, const Team& team1) {
    // Implement this placeholder.
    return true;
  }

 private:
  struct Player {
    bool operator<(const Player& that) const { return height < that.height; }

    int height;
  };

  vector<Player> players_;
};

void ValidPlacementExistsWrapper(TimedExecutor& executor,
                                 const vector<int>& team0,
                                 const vector<int>& team1, bool expected_01,
                                 bool expected_10) {
  Team t0(team0), t1(team1);

  bool result_01 =
      executor.Run([&] { return Team::ValidPlacementExists(t0, t1); });
  bool result_10 =
      executor.Run([&] { return Team::ValidPlacementExists(t1, t0); });

  if (result_01 != expected_01 || result_10 != expected_10) {
    throw TestFailure("");
  }
}

int main(int argc, char* argv[]) {
  // The timeout is set to 15 seconds for each test case.
  // If your program ends with TIMEOUT error, and you want to try longer time
  // limit, you can extend the limit by changing the following line.
  std::chrono::seconds timeout_seconds{15};

  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "team0", "team1",
                                       "expected_01", "expected_10"};
  return GenericTestMain(args, timeout_seconds, "is_array_dominated.tsv",
                         &ValidPlacementExistsWrapper, DefaultComparator{},
                         param_names);
}
