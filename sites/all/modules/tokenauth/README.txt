# Token Authentication

Enable feed readers and other simple clients to see certain private pages by 
providing an authentication token.

## Usage

If you put token=x on the querystring and x is a valid token, then an anonymous 
user will be authenticated as the user who owns the token. You may learn a user's 
token by clicking on the tab on the user's profile page.

## Administration

Go to admin/config/services/tokenauth to configure this module.

### Security

In configuring Token Authentication, be sure to use it with 'low security' 
content only. Tokenauth transmits what amounts to a password in the clear via URL, 
you should assume anyone interested can get ahold of it and use it. Tokenauth 
should be used for functionality requiring user identification more than user 
authentication.

## Developers

Use tokenauth_text_load() to build UIs using the configurable use text.
Use tokenauth_reset_user_form() to get a reset token button.

## Todo
* use the token in other contexts like inbound email (see mailhandler.module)
  
