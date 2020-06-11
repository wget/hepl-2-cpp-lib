# HEPL - 2 - CPP Lib

A simple lib shared across several CPP projects (CPP Project Calculator and Statistics).

Requires a C++11 compiler. Only tested with GNU GCC on Arch Linux.

## Template declarations and template definitions

We previously used `.ipp` files to store the "implementation" of our class templates and a `.hpp` to store their declarations. However, even if I'm most of the time a vimmer, having the `.ipp` extension not being recognized by some common GUI development tools like KDevelop or QtCreator was annoying, especially when we wanted to use these tools for the ease of debugging.

Some previous guidelines encouraged the use of [`.inl` files](https://stackoverflow.com/a/1208062/3514658) instead.

While having two files is still great [for convenience](https://stackoverflow.com/q/495021/3514658), this is now a practise that [isn't followed any more](https://google.github.io/styleguide/cppguide.html#Self_contained_Headers). We have decided to move the content of these `.ipp` files to the end of their `.hpp` counterparts, respecting forward declarations when present.

## Class Template vs Template Class

There is a [distinction](https://web.archive.org/web/20190619094605/https://bogotobogo.com/cplusplus/template_declaration_definition_header_implementation_file.php#template_class_vs_class_template) between class template and template class:

* Class template is a template used to generate template classes.
* Template class is an instance of a class template.
