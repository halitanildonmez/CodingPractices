from_range = 1
to_range = 11

sum_squares = sum(x*x for x in range(from_range, to_range))
sum_values = sum(x for x in range(from_range, to_range))

print ((sum_values * sum_values) - sum_squares)
