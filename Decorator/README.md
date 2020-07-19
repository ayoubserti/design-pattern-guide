# Abstract
`Decorator` is a structural design pattern, it lets you wrap a legacy class and change it's behaviour without the need to patch it. It's very commun to have a legacy code that works fine and you have to add new features.

For instance, You have an application that use write documents as docx and you want to provide new ways for users. They might customize the method they want there documents to be filled: markdown, brut text, pdf, rtf, epub, ... or even a combinaision of those.

Let's admit the legacy class was: `DocGenerator`. It provide a function called `generate(filepath)`

You might want to introduce an interface `IGenerator` that have same function prototype `generate(filename)`, then inherent `DocGenerator` from `IGenerator` and create a new `Generator` Decorator class which is the mother class of all other substitutions.