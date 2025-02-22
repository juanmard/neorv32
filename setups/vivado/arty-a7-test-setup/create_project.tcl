set board "A7-35"

# create and clear output directory
set outputdir work
file mkdir $outputdir

set files [glob -nocomplain "$outputdir/*"]
if {[llength $files] != 0} {
    puts "deleting contents of $outputdir"
    file delete -force {*}[glob -directory $outputdir *]; # clear folder contents
} else {
    puts "$outputdir is empty"
}

switch $board {
  "A7-35" {
    set a7part "xc7a35ticsg324-1L"
    set a7prj "arty-a7-35-test-setup"
  }
}

# create project
create_project -part $a7part $a7prj $outputdir

# add source files: core sources
add_files [glob ./../../../rtl/core/*.vhd]
set_property library neorv32 [get_files [glob ./../../../rtl/core/*.vhd]]

# add source file: top entity
add_files [glob ./../../../rtl/templates/processor/neorv32_ProcessorTop_Test.vhd]

# add source files: simulation-only
add_files -fileset sim_1 [list ./../../../sim/neorv32_tb.simple.vhd ./../../../sim/uart_rx.simple.vhd]

# add source files: constraints
add_files -fileset constrs_1 [glob ./*.xdc]

# run synthesis, implementation and bitstream generation
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
