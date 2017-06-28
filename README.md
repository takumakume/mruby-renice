# mruby-renice   [![Build Status](https://travis-ci.org/takumakume/mruby-renice.svg?branch=master)](https://travis-ci.org/takumakume/mruby-renice)

getpriority(2)/setpriority(2) for mruby, it like renice(1)

## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'takumakume/mruby-renice'
end
```

## usage

- for process

  ```ruby
  Renice::Process.get(pid)
  #=> 0

  Renice::Process.set(pid, prio)
  #=> true or raise
  ```

- for process group

  ```ruby
  Renice::ProcessGroup.get(pgid)
  Renice::ProcessGroup.set(pgid, prio)
  ```

- for process group

  ```ruby
  Renice::User.get(uid)
  Renice::User.set(uid, prio)
  ```

## License

under the MIT License:

- see LICENSE file
