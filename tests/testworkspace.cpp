#include <cassert>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdio>

#include "Document.hpp"
#include "Prompt.hpp"
#include "Message.hpp"
#include "Workspace.hpp"
//tests that the prompt stores the correct values 
void prompt_smoke_test() {
    Prompt p("Reviewer", "Review this requirement.");

    assert(p.title() == "Reviewer");
    assert(p.text() == "Review this requirement.");
    assert(!p.empty());

    Prompt same("Reviewer", "Review this requirement.");
    Prompt different("Writer", "Write something.");

    assert(p == same);
    assert(p != different);
}
//tests the message role, text, empty, and compare functions
void message_test() {
    Message m(MessageRole::User, "Hello");

    assert(m.role() == MessageRole::User);
    assert(m.text() == "Hello");
    assert(!m.empty());

    Message same(MessageRole::User, "Hello");
    Message different(MessageRole::Assistant, "Hello");

    assert(m == same);
    assert(m != different);
}

//tests the document values and functions 
void document_test() {
    Document d("Test", "Hello");

    assert(d.title() == "Test");
    assert(d.contents() == "Hello");
    assert(d.characterCount() == 5);
    assert(!d.empty());

    Document same("Test", "Hello");
    Document different("Other", "Hello");

    assert(d == same);
    assert(d != different);
}
//tests that the document can load a file
void document_load_test() {
    std::ofstream file("test_load.txt");
    file << "This is a test.";
    file.close();

    Document d;

    bool loaded = d.load("test_load.txt");

    assert(loaded);
    assert(d.title() == "test_load.txt");
    assert(d.sourcePath() == "test_load.txt");
    assert(d.contents() == "This is a test.");

    std::remove("test_load.txt");
}
//tests that a failed load doesnt change the doc

void document_failed_load_test() {
    Document d("Original", "Original contents");

    bool loaded = d.load("does_not_exist.txt");

    assert(!loaded);

    assert(d.title() == "Original");
    assert(d.contents() == "Original contents");
    assert(d.sourcePath().empty());
}
//tests adding and retrieving items from a workspace
void workspace_smoke_test() {
    Workspace w("Demo");

    w.addDocument(Document("Doc", "Document text"));
    w.addPrompt(Prompt("Reviewer", "Review this."));
    w.addMessage(Message(MessageRole::User, "Hello"));

    assert(w.name() == "Demo");

    assert(w.documentCount() == 1);
    assert(w.promptCount() == 1);
    assert(w.messageCount() == 1);

    assert(w.documentAt(0).title() == "Doc");
    assert(w.promptAt(0).title() == "Reviewer");
    assert(w.messageAt(0).text() == "Hello");
}
//tests that an invalid index throws an exception
void invalid_index_test() {
    Workspace w("Demo");

    bool threwException = false;

    try {
        w.documentAt(0);
    }
    catch (const std::out_of_range&) {
        threwException = true;
    }

    assert(threwException);
}
//tests that a copied workspace is independent
void copy_test() {
    Workspace original("Original");
    original.addPrompt(Prompt("Prompt", "Original text"));

    Workspace copy = original;

    original.setName("Changed");
    original.promptAt(0).setText("Changed text");

    
    assert(copy.name() == "Original");
    assert(copy.promptAt(0).text() == "Original text");
}

//runs all the tests
int main() {
    prompt_smoke_test();
    message_test();
    document_test();
    document_load_test();
    document_failed_load_test();
    workspace_smoke_test();
    invalid_index_test();
    copy_test();

    std::cout << "M0 tests passed\n";
    return 0;
}
