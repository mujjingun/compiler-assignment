
using Base.Filesystem

function parse_output(output)
    lines = split(output, '\n')
    return filter(line-> occursin("error", line) || occursin("error", lowercase.(line)), lines);
end

function main()
    filenames = map(x->"error" * string(x) * ".c", 1:15)
    filenames = map(x->joinpath("test_files", x), filenames)
    
    for name in filenames
        output = read(`./project3_16 $name`, String)
        parsed = parse_output(output)

        println("-- compiling: ", name)
        for i in parsed
            println(parsed)
        end
        print('\n')
    end
end

main()
