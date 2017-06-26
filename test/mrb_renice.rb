##
## Renice Test
##

assert("Renice#hello") do
  t = Renice.new "hello"
  assert_equal("hello", t.hello)
end

assert("Renice#bye") do
  t = Renice.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Renice.hi") do
  assert_equal("hi!!", Renice.hi)
end
