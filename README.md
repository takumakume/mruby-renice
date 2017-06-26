# mruby-renice   [![Build Status](https://travis-ci.org/takumakume/mruby-renice.svg?branch=master)](https://travis-ci.org/takumakume/mruby-renice)
Renice class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'takumakume/mruby-renice'
end
```
## example
```ruby
p Renice.hi
#=> "hi!!"
t = Renice.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
