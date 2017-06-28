assert('Renice::Process.get') do
  assert_equal(0, Renice::Process.get(Process.pid))
end

assert('Renice::Process.set') do
  assert_true(Renice::Process.set(Process.pid, 1))
  assert_equal(1, Renice::Process.get(Process.pid))
  assert_raise(RuntimeError, "The caller attempted to set a lower nice value, but did not have the required privilege (on CAP_SYS_NICE)") do
    Renice::Process.set(Process.pid, 0)
  end
  assert_equal(1, Renice::Process.get(Process.pid))
end

assert('Renice::ProcessGroup.get') do
  assert_raise(RuntimeError, "No process was located using the which and who values specified (mrbgems: mruby-renice)") do
    Renice::ProcessGroup.get(Process.pid)
  end
end

assert('Renice::ProcessGroup.set') do
  assert_raise(RuntimeError, "No process was located using the which and who values specified (mrbgems: mruby-renice)") do
    Renice::ProcessGroup.set(Process.pid, 1)
  end
end

assert('Renice::User.get') do
  assert_equal(0, Renice::User.get(Process::Sys.getuid))
end

assert('Renice::User.set') do
  assert_raise(RuntimeError, "The caller attempted to set a lower nice value, but did not have the required privilege (on CAP_SYS_NICE)") do
    Renice::User.set(Process::Sys.getuid, -19)
  end
end
