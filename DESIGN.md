# M0 Design and Understanding Note

Answer briefly in your own words. This is not intended to be a long report.

1. What responsibility belongs to `Workspace`, and what responsibilities belong to `Document`, `Prompt`, and `Message` instead?

`Workspace` is used for storing and organizing collections of `Document`, `Prompt`, and `Message` objects. `Document` handles text content and file loading, `Prompt` stores reusable prompt text, and `Message` stores conversation text along with its role.


2. Why are the collections inside `Workspace` private? Explain the purpose of the const and non-const `At` overloads.

The collections inside `Workspace` are private so they can only be accessed through the class’ public functions. The non-const `At` overloads allow stored objects to be changed, while the const overloads mean read only.

3. Explain one meaningful test you added. What behavior does it check, and what implementation error could it catch?

One meaningful test I added checks what happens when a document tries to load a file that does not exist. It makes sure `load()` returns false and that the document’s previous content isnt changed. This could catch something that changes the object before checking whether the file opened successfully.
4. Describe one implementation decision that you verified, tested, or revised before submitting your work.

One implementation decision I revised was how I read the entire contents of a file. I first considered reading it line by line, but I changed it to use a string stream so that the file contents would be preserved more accurately.

5. If generative AI was used, disclose it as required by course policy. If no generative AI was used, state that. The disclosure itself is not used as proof of authorship or understanding.

I used generative AI as a programming aid to help interpret the assignment requirements and help explain parts of the code. I coded and tested the final code myself and I am responsible for the submitted work.