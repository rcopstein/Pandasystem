# PandaSystem V1.0
### Create by Rafael Copstein and João Pedro Pianta

PandaSystem is a Filesystem emulator designed to study the FAT file system architecture.

To get started, use *init* to create a new filesystem file.
Next, use *load* to load it into memory (not all of it, don't worry).
Remember to always use the *load* command when you start the program.

The following commands shall guide you:

    > ls <path>
      Describes the contents of the folder pointed by <path>

    > create <path>/<filename>
      Creates a new empty file named <filename> at the location pointed
      by <path>

    > write "<content>" <path>/<filename>
      Writes <content> to the file named <filename> at the location
      pointed by <path>. This will overwrite any previous content in
      that file.

    > append "<content>" <path>/<filename>
      Appends <content> to the end of the file name <filename> at the
      location pointed by <path>. This will not erase previously written
      content.

    > read <path>/<filename>
      Reads the contents of the file named <filename> at the location
      pointed by <path>.

    > unlink <path> | unlink <path>/<filename>
      Deletes the files named <filename> at the location pointed by
      <path>. If <filename> is not provided, the folder pointed by
      <path> will be deleted instead. Note that the folder must be empty
      in order to be deleted.