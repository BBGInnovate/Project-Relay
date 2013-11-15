
/*
 * jQuery treeTable Plugin 2.3.0
 * http://ludo.cubicphuse.nl/jquery-plugins/treeTable/
 *
 * Copyright 2010, Ludo van den Boom
 * Dual licensed under the MIT or GPL Version 2 licenses.
 */
(function($) {
  // Helps to make options available to all functions
  // TODO: This gives problems when there are both expandable and non-expandable
  // trees on a page. The options shouldn't be global to all these instances!
  var options;
  var defaultPaddingLeft;

  $.fn.treeTable = function(opts) {
    options = $.extend({}, $.fn.treeTable.defaults, opts);

    return this.each(function() {
      $(this).addClass("treeTable").find("tbody tr").each(function() {
        // Initialize root nodes only if possible
        if(!options.expandable || $(this)[0].className.search(options.childPrefix) == -1) {
          // To optimize performance of indentation, I retrieve the padding-left
          // value of the first root node. This way I only have to call +css+
          // once.
          if (isNaN(defaultPaddingLeft)) {
            defaultPaddingLeft = parseInt($($(this).children("td")[options.treeColumn]).css('padding-left'), 10);
          }

          initialize($(this));
        } else if(options.initialState == "collapsed") {
          this.style.display = "none"; // Performance! $(this).hide() is slow...
        }
      });
    });
  };

  $.fn.treeTable.defaults = {
    childPrefix: "child-of-",
    clickableNodeNames: false,
    expandable: true,
    indent: 19,
    initialState: "collapsed",
    treeColumn: 0
  };

  // Recursively hide all node's children in a tree
  $.fn.collapse = function() {
    $(this).addClass("collapsed");

    childrenOf($(this)).each(function() {
      if(!$(this).hasClass("collapsed")) {
        $(this).collapse();
      }

      this.style.display = "none"; // Performance! $(this).hide() is slow...
    });

    return this;
  };

  // Recursively show all node's children in a tree
  $.fn.expand = function() {
    $(this).removeClass("collapsed").addClass("expanded");

    childrenOf($(this)).each(function() {
      initialize($(this));

      if($(this).is(".expanded.parent")) {
        $(this).expand();
      }

      // this.style.display = "table-row"; // Unfortunately this is not possible with IE :-(
      $(this).show();
    });

    return this;
  };

  // Reveal a node by expanding all ancestors
  $.fn.reveal = function() {
    $(ancestorsOf($(this)).reverse()).each(function() {
      initialize($(this));
      $(this).expand().show();
    });

    return this;
  };

  // Add an entire branch to +destination+
  $.fn.appendBranchTo = function(destination) {
    var node = $(this);
    var parent = parentOf(node);

    var ancestorNames = $.map(ancestorsOf($(destination)), function(a) { return a.id; });

    // Conditions:
    // 1: +node+ should not be inserted in a location in a branch if this would
    //    result in +node+ being an ancestor of itself.
    // 2: +node+ should not have a parent OR the destination should not be the
    //    same as +node+'s current parent (this last condition prevents +node+
    //    from being moved to the same location where it already is).
    // 3: +node+ should not be inserted as a child of +node+ itself.
    if($.inArray(node[0].id, ancestorNames) == -1 && (!parent || (destination.id != parent[0].id)) && destination.id != node[0].id) {
      indent(node, ancestorsOf(node).length * options.indent * -1); // Remove indentation

      if(parent) { node.removeClass(options.childPrefix + parent[0].id); }

      node.addClass(options.childPrefix + destination.id);
      move(node, destination); // Recursively move nodes to new location
      indent(node, ancestorsOf(node).length * options.indent);
    }

    return this;
  };

  // Add reverse() function from JS Arrays
  $.fn.reverse = function() {
    return this.pushStack(this.get().reverse(), arguments);
  };

  // Toggle an entire branch
  $.fn.toggleBranch = function() {
    if($(this).hasClass("collapsed")) {
      $(this).expand();
    } else {
      $(this).removeClass("expanded").collapse();
    }

    return this;
  };

  // === Private functions

  function ancestorsOf(node) {
    var ancestors = [];
    while(node = parentOf(node)) {
      ancestors[ancestors.length] = node[0];
    }
    return ancestors;
  };

  function childrenOf(node) {
    return $(node).siblings("tr." + options.childPrefix + node[0].id);
  };

  function getPaddingLeft(node) {
    var paddingLeft = parseInt(node[0].style.paddingLeft, 10);
    return (isNaN(paddingLeft)) ? defaultPaddingLeft : paddingLeft;
  }

  function indent(node, value) {
    var cell = $(node.children("td")[options.treeColumn]);
    cell[0].style.paddingLeft = getPaddingLeft(cell) + value + "px";

    childrenOf(node).each(function() {
      indent($(this), value);
    });
  };

  function initialize(node) {
    if(!node.hasClass("initialized")) {
      node.addClass("initialized");

      var childNodes = childrenOf(node);

      if(!node.hasClass("parent") && childNodes.length > 0) {
        node.addClass("parent");
      }

      if(node.hasClass("parent")) {
        var cell = $(node.children("td")[options.treeColumn]);
        var padding = getPaddingLeft(cell) + options.indent;

        childNodes.each(function() {
          $(this).children("td")[options.treeColumn].style.paddingLeft = padding + "px";
        });

        if(options.expandable) {
          cell.prepend('<span style="margin-left: -' + options.indent + 'px; padding-left: ' + options.indent + 'px" class="expander"></span>');
          $(cell[0].firstChild).click(function() { node.toggleBranch(); });

          if(options.clickableNodeNames) {
            cell[0].style.cursor = "pointer";
            $(cell).click(function(e) {
              // Don't double-toggle if the click is on the existing expander icon
              if (e.target.className != 'expander') {
                node.toggleBranch();
              }
            });
          }

          // Check for a class set explicitly by the user, otherwise set the default class
          if(!(node.hasClass("expanded") || node.hasClass("collapsed"))) {
            node.addClass(options.initialState);
          }

          if(node.hasClass("expanded")) {
            node.expand();
          }
        }
      }
    }
  };

  function move(node, destination) {
    node.insertAfter(destination);
    childrenOf(node).reverse().each(function() { move($(this), node[0]); });
  };

  function parentOf(node) {
    var classNames = node[0].className.split(' ');

    for(key in classNames) {
      if(classNames[key].match(options.childPrefix)) {
        return $(node).siblings("#" + classNames[key].substring(options.childPrefix.length));
      }
    }
  };
})(jQuery);
;

/**
 * Cookie plugin 1.0
 *
 * Copyright (c) 2006 Klaus Hartl (stilbuero.de)
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 *
 */
jQuery.cookie=function(b,j,m){if(typeof j!="undefined"){m=m||{};if(j===null){j="";m.expires=-1}var e="";if(m.expires&&(typeof m.expires=="number"||m.expires.toUTCString)){var f;if(typeof m.expires=="number"){f=new Date();f.setTime(f.getTime()+(m.expires*24*60*60*1000))}else{f=m.expires}e="; expires="+f.toUTCString()}var l=m.path?"; path="+(m.path):"";var g=m.domain?"; domain="+(m.domain):"";var a=m.secure?"; secure":"";document.cookie=[b,"=",encodeURIComponent(j),e,l,g,a].join("")}else{var d=null;if(document.cookie&&document.cookie!=""){var k=document.cookie.split(";");for(var h=0;h<k.length;h++){var c=jQuery.trim(k[h]);if(c.substring(0,b.length+1)==(b+"=")){d=decodeURIComponent(c.substring(b.length+1));break}}}return d}};
;
(function ($) {

/**
 * Retrieves the summary for the first element.
 */
$.fn.drupalGetSummary = function () {
  var callback = this.data('summaryCallback');
  return (this[0] && callback) ? $.trim(callback(this[0])) : '';
};

/**
 * Sets the summary for all matched elements.
 *
 * @param callback
 *   Either a function that will be called each time the summary is
 *   retrieved or a string (which is returned each time).
 */
$.fn.drupalSetSummary = function (callback) {
  var self = this;

  // To facilitate things, the callback should always be a function. If it's
  // not, we wrap it into an anonymous function which just returns the value.
  if (typeof callback != 'function') {
    var val = callback;
    callback = function () { return val; };
  }

  return this
    .data('summaryCallback', callback)
    // To prevent duplicate events, the handlers are first removed and then
    // (re-)added.
    .unbind('formUpdated.summary')
    .bind('formUpdated.summary', function () {
      self.trigger('summaryUpdated');
    })
    // The actual summaryUpdated handler doesn't fire when the callback is
    // changed, so we have to do this manually.
    .trigger('summaryUpdated');
};

/**
 * Sends a 'formUpdated' event each time a form element is modified.
 */
Drupal.behaviors.formUpdated = {
  attach: function (context) {
    // These events are namespaced so that we can remove them later.
    var events = 'change.formUpdated click.formUpdated blur.formUpdated keyup.formUpdated';
    $(context)
      // Since context could be an input element itself, it's added back to
      // the jQuery object and filtered again.
      .find(':input').andSelf().filter(':input')
      // To prevent duplicate events, the handlers are first removed and then
      // (re-)added.
      .unbind(events).bind(events, function () {
        $(this).trigger('formUpdated');
      });
  }
};

/**
 * Prepopulate form fields with information from the visitor cookie.
 */
Drupal.behaviors.fillUserInfoFromCookie = {
  attach: function (context, settings) {
    $('form.user-info-from-cookie').once('user-info-from-cookie', function () {
      var formContext = this;
      $.each(['name', 'mail', 'homepage'], function () {
        var $element = $('[name=' + this + ']', formContext);
        var cookie = $.cookie('Drupal.visitor.' + this);
        if ($element.length && cookie) {
          $element.val(cookie);
        }
      });
    });
  }
};

})(jQuery);
;
