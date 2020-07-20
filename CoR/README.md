# Abstract 
`Chain of Responsibility`, a behavioral design pattern that allows client to chainnel request along a chain of handlers. Every handler may decide to process the request or to pass it to the next chain.

You might think of handlers like a middlewares which catch/pass the request to the next.
`express.js` is a great example of `Chain of Responsibility` design pattern
