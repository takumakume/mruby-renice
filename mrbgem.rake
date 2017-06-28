MRuby::Gem::Specification.new('mruby-renice') do |spec|
  spec.license = 'MIT'
  spec.authors = 'takumakume'
  spec.add_test_dependency 'mruby-print'
  spec.add_test_dependency 'mruby-process'
  spec.add_test_dependency 'mruby-process-sys', github: 'haconiwa/mruby-process-sys'
end
