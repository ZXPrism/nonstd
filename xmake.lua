set_project("nonstd")

add_rules("mode.debug", "mode.release")
add_requires("doctest", "nanobench")

target("nonstd")
    set_languages("cxx23")
    set_kind("binary")
    set_warnings("all", "error")

    add_includedirs("src")
    add_files("src/**.cpp")

    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
    end)
target_end()

rule("test")
    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
    end)
rule_end()

rule("bench")
    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
    end)
rule_end()

-- test
for _, file in ipairs(os.files("test/*.cpp")) do
    local name = "test_" .. path.basename(file)
    target(name)
        set_languages("cxx23")
        set_kind("binary")
        add_files(file)
        add_packages("doctest")
        add_includedirs("src", "test")
        add_rules("test")
    target_end()
end

-- bench
for _, file in ipairs(os.files("benchmark/*.cpp")) do
    local name = "bench_" .. path.basename(file)
    target(name)
        set_languages("cxx23")
        set_kind("binary")
        add_files(file)
        add_packages("nanobench")
        add_includedirs("src", "benchmark")
        add_rules("bench")
    target_end()
end
